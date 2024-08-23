#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x92997ed8, "_printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x800473f, "__cond_resched" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x647af474, "prepare_to_wait_event" },
	{ 0x1000e51, "schedule" },
	{ 0x49970de8, "finish_wait" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0x3d87ed5b, "gpio_to_desc" },
	{ 0xb4ca5a15, "gpiod_set_raw_value" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x5f754e5a, "memset" },
	{ 0x6ef2132f, "module_put" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xdc0e4855, "timer_delete" },
	{ 0x37a0cba, "kfree" },
	{ 0xa68613dd, "get_jiffies_64" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x943b4d0f, "gpiod_direction_input" },
	{ 0x39cf4498, "gpiod_direction_output_raw" },
	{ 0x657fc34a, "gpiod_get_raw_value" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xfe990052, "gpio_free" },
	{ 0x637493f3, "__wake_up" },
	{ 0xa3680b0e, "try_module_get" },
	{ 0x7b8180e0, "kmalloc_caches" },
	{ 0x2349da1b, "kmalloc_trace" },
	{ 0x9cc32aaf, "gpiod_to_irq" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x82ee90dc, "timer_delete_sync" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x24d273d1, "add_timer" },
	{ 0x43838dc4, "__register_chrdev" },
	{ 0x31ce3c7c, "param_ops_int" },
	{ 0x65a4ef4c, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "DD08AEAFD04DCF4DA6C0001");
