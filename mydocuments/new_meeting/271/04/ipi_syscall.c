/**
 * (20150317) FUJITA
 * Create interrupt handler
 * and IPI-syscall for b4-training
 */

#include<asm/apic.h> /* apic_icr_write(), apic_wait_icr_idle() */
#include<asm/apicdef.h> /* APIC_INT_ASSERT, APIC_DEST_PHYSICAL */
#include<asm-generic/percpu.h> /* per_cpu() */
#include<linux/interrupt.h> /* request_irq() */
#include<linux/kernel.h>
#include<linux/module.h> 

#define NUM_OF_CORE 4

/**
 * message_handler - interrupt handler which print message 
 */
irqreturn_t message_handler(int irq,void *dev){
    printk("Recieved IPI\n");
    return IRQ_HANDLED;
}

/**
 * request_ipi_irq - register message_handler
 * @vector: vector number which register message_handler 
 * Return irq: IRQ number which message_handler registered
 */
asmlinkage int request_ipi_irq(int vector)
{
 int irq;
 int ret;
 int i;
 printk("request_ipi_start\n");
 for(irq = 16; irq < 999; irq++){
 ret = request_irq(irq, message_handler, 
 0x00000000, "message_handler", NULL);
 if(ret == 0) break;
 }
 if(ret != 0) return ret;

 for(i = 0; i < NUM_OF_CORE; i++)
 per_cpu(vector_irq, i)[vector] = irq;

 return irq;
}

/**
 * send_ipi - send IPI
 * @core_id: recieve core 
 * @vector:  vector 
 * Return 0: succeed
 */
asmlinkage void send_ipi(int core_id, int vector)
{
    int phys_apicid;
    
    phys_apicid = per_cpu(x86_bios_cpu_apicid, core_id);

    apic_icr_write(APIC_INT_ASSERT | APIC_DEST_PHYSICAL | 
            vector, phys_apicid);

    apic_wait_icr_idle();
}
