#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/ioport.h>
#include<linux/delay.h>

#define PCI_INDEX_PORT 0xCF8
#define PCI_DATA_PORT 0xCFC
#define PCI_NOT_FOUND_ERROR 0xFFFF


unsigned short read_pci_config_short(unsigned char bus, unsigned char slot, unsigned char func,\
                                      unsigned char offset)
{
    unsigned short config;
    outl(0x80000000|(bus<<16)|(slot<<11)|(func<<8)| offset, PCI_INDEX_PORT);
    config = inw(PCI_DATA_PORT + (offset&2));

    return config;
}

static int __init pci_init(void)
{
    unsigned short vendor_id;
    unsigned short device_id;

    vendor_id = read_pci_config_short(3, 0, 0, 0);
    device_id = read_pci_config_short(3, 0, 0, 2);

    if((vendor_id == PCI_NOT_FOUND_ERROR) || (device_id == PCI_NOT_FOUND_ERROR))
    {
       goto pcie_error;
    }
    pr_info("Vendor ID : %02x\t  Device ID: %02x\n", vendor_id, device_id);

    pcie_error:
        pr_err("Requested Pci is not found");

   return 0;
}

static void __exit pci_exit(void)
{

   pr_info("Pci Driver: Removed");

}


module_init(pci_init);
module_exit(pci_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VISHAL VERMA");

