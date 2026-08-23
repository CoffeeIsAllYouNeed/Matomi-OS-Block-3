
#include <linux/proc_fs.h>

#include <linux/seq_file.h>

#include <linux/mm.h>

#include <linux/init.h>

#include <linux/ktime.h>

static int matomi_stats_show(struct seq_file *m, void *v)

{

	struct sysinfo si;

	si_meminfo(&si);

	seq_printf(m, "MatomiOS Stats\n");

	seq_printf(m, "TotalRAM_kB: %lu\n", si.totalram << (PAGE_SHIFT - 10));

	seq_printf(m, "FreeRAM_kB: %lu\n", si.freeram << (PAGE_SHIFT - 10));

	seq_printf(m, "Uptime_sec: %lld\n", ktime_get_seconds());

	return 0;

}

static int matomi_stats_open(struct inode *inode, struct file *file)

{

	return single_open(file, matomi_stats_show, NULL);

}

static const struct proc_ops matomi_stats_ops = {

	.proc_open = matomi_stats_open,

	.proc_read = seq_read,

	.proc_lseek = seq_lseek,

	.proc_release = single_release,

};

static int __init matomi_stats_init(void)

{

	proc_create("matomi_stats", 0444, NULL, &matomi_stats_ops);

	return 0;

}

fs_initcall(matomi_stats_init);

