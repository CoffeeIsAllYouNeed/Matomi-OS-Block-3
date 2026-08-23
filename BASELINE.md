# Matomi-OS Phase 1 Baseline

Kernel: v6.12, `matomi-os-base` branch, build #1
Repo: CoffeeIsAllYouNeed/Matomi-OS-Block-3
Environment: WSL2 (Ubuntu), 16-core host, QEMU 10.2.1

## Boot + shell test
- Kernel boots successfully via QEMU (`-kernel bzImage -initrd rootfs.img`)
- Lands at working BusyBox shell (`~ #`)
- Init note: kernel runs `/bin/sh` as init directly rather than our custom
  `/init` script, even with `rdinit=/init` passed. Not yet root-caused. Does
  not block functionality — `/proc` and `/sys` can be mounted manually once
  at the shell. Fix later if needed; not blocking.

## Memory (from /proc/meminfo, after manual mount)
- MemTotal: 89,988 kB (~90MB) — this is QEMU's default allocated RAM, not host RAM
- MemFree: 77,332 kB (~77MB)
- MemAvailable: 75,648 kB
- Buffers: 0 kB
- Cached: 2,144 kB

## Timing
- Full session (boot + idle shell time before manual quit): 1m6.252s real
  (rough figure — includes manual interaction time, not pure boot latency;
  re-measure with a scripted/automated boot exit for a precise number later)
- user: 6.734s / sys: 0.561s (QEMU host-side CPU time)

## Build artifacts
- bzImage size: 15M
- Full source tree size (post-build): 3.0G

## What this baseline is for
Every future kernel patch (Phase 2: scheduler tuning, huge pages, NUMA,
io_uring, etc.) gets compared against these numbers. A patch is only "worth
keeping" if it measurably improves one of these without regressing the others
— e.g. faster boot, lower memory footprint, or (once real workloads are
running) better token/sec or latency on an actual AI inference/agent task.

## Known TODOs before Phase 2
- [ ] Get a precise, automated boot-time measurement (script that boots QEMU
      with a fixed workload and exits automatically, rather than manual quit)
- [ ] Root-cause why `/init` isn't picked up as PID 1 instead of `/bin/sh`
- [ ] Increase QEMU's allocated RAM (`-m` flag) to something closer to a
      realistic target machine before running any AI workload tests
- [ ] Attach a real disk image instead of initramfs-only, if persistent
      storage is needed for later phases
