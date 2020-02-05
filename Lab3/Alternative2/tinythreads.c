#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "tinythreads.h"

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4


struct thread_block {
    void (*function)(int);   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

	
	// LCD
	CLKPR = 0x80;
	CLKPR = 0x00;

	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
	LCDCRB = (1 << LCDMUX0) | (1 << LCDMUX1) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	
	// Button
	PORTB += (1<<PB7);
	DDRB = (1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
		
	//Insert nop for synchronization
	asm("nop");
	
	// Timer
	PCMSK1 = (1 << PCINT15);
	EIMSK = (1 << PCIE1);
	TIMSK1 = (1 << OCIE1A);	
	//TCCR0A = (1 << WGM01) | (1 << WGM00);		Tappert försök
	TCCR1A = (1 << COM1A1) | (1 << COM1A0);
	TCCR1B = (1 << CS12);
	OCR1A = 781.25;
	TCNT1 = 0;
	
	
    initialized = 1;
}

static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
		p->next = q;
		*queue = p;
		
		
    }
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;

    DISABLE();
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    enqueue(newp, &readyQ);
    ENABLE();
}

void yield(void) {
	DISABLE();
    //enqueue (current, &readyQ);
	dispatch(dequeue(&readyQ));
	ENABLE();
}

void lock(mutex *m) {
	DISABLE();
	if(m->locked){
		m->waitQ = current;
		dispatch(&readyQ);	
	}
	else{	

		m->locked = true;
	}
	ENABLE();
}

void unlock(mutex *m) {
	DISABLE();
	if (m->waitQ)
	{
		//thread t = m->waitQ;

		//m->waitQ = NULL;
		//enqueue(m->waitQ, &readyQ);
		dispatch(m->waitQ);		
	}
	else{
		m->locked = false;
	}
	ENABLE();
}


mutex mutexBlink;
ISR(TIMER1_COMPA_vect) { 
	
	unlock(&mutexBlink);

	//yield();
}


mutex mutexButton;
ISR(PCINT1_vect) {
	
	unlock(&mutexButton);
	//yield();
}
