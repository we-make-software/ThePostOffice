#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe3272708, "__kmalloc_cache_noprof" },
	{ 0x92997ed8, "_printk" },
	{ 0xb43f9365, "ktime_get" },
	{ 0x10709678, "GetTheMailConditioner" },
	{ 0x37a0cba, "kfree" },
	{ 0x953e1b9e, "ktime_get_real_seconds" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x158971cf, "StopExpiryWorkBase" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x99e92706, "kmalloc_caches" },
	{ 0xf9108d3, "module_layout" },
};

MODULE_INFO(depends, "TheMailConditioner,ExpiryWorkBase");

