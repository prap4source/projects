==23913== Memcheck, a memory error detector
==23913== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==23913== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==23913== Command: bin/cproject tests
==23913== 
--23913-- Valgrind options:
--23913--    -v
--23913--    --tool=memcheck
--23913--    --leak-check=yes
--23913--    --leak-check=full
--23913--    --show-leak-kinds=all
--23913--    --track-origins=yes
--23913-- Contents of /proc/version:
--23913--   Linux version 3.10.0-327.28.3.el7.x86_64 (mockbuild@x86-ol7-builder-02) (gcc version 4.8.5 20150623 (Red Hat 4.8.5-4) (GCC) ) #1 SMP Thu Aug 18 09:36:48 PDT 2016
--23913-- 
--23913-- Arch and hwcaps: AMD64, LittleEndian, amd64-cx16-lzcnt-rdtscp-sse3-avx-avx2-bmi
--23913-- Page sizes: currently 4096, max supported 4096
--23913-- Valgrind library directory: /usr/lib64/valgrind
--23913-- Reading syms from /homes/pgopanapalli/ws/FILES/Imp_Notes/git-hub/projects/bin/cproject
--23913-- Reading syms from /usr/lib64/ld-2.17.so
--23913-- Reading syms from /usr/lib64/valgrind/memcheck-amd64-linux
--23913--    object doesn't have a symbol table
--23913--    object doesn't have a dynamic symbol table
--23913-- Scheduler: using generic scheduler lock implementation.
--23913-- Reading suppressions file: /usr/lib64/valgrind/default.supp
==23913== embedded gdbserver: reading from /tmp/vgdb-pipe-from-vgdb-to-23913-by-pgopanap-on-pgopanap-linux
==23913== embedded gdbserver: writing to   /tmp/vgdb-pipe-to-vgdb-from-23913-by-pgopanap-on-pgopanap-linux
==23913== embedded gdbserver: shared mem   /tmp/vgdb-pipe-shared-mem-vgdb-23913-by-pgopanap-on-pgopanap-linux
==23913== 
==23913== TO CONTROL THIS PROCESS USING vgdb (which you probably
==23913== don't want to do, unless you know exactly what you're doing,
==23913== or are doing some strange experiment):
==23913==   /usr/lib64/valgrind/../../bin/vgdb --pid=23913 ...command...
==23913== 
==23913== TO DEBUG THIS PROCESS USING GDB: start GDB like this
==23913==   /path/to/gdb bin/cproject
==23913== and then give GDB the following command
==23913==   target remote | /usr/lib64/valgrind/../../bin/vgdb --pid=23913
==23913== --pid is optional if only one valgrind process is running
==23913== 
--23913-- REDIR: 0x4018e90 (ld-linux-x86-64.so.2:strlen) redirected to 0x38056d91 (???)
--23913-- REDIR: 0x4018c60 (ld-linux-x86-64.so.2:index) redirected to 0x38056dab (???)
--23913-- Reading syms from /usr/lib64/valgrind/vgpreload_core-amd64-linux.so
--23913-- Reading syms from /usr/lib64/valgrind/vgpreload_memcheck-amd64-linux.so
==23913== WARNING: new redirection conflicts with existing -- ignoring it
--23913--     old: 0x04018e90 (strlen              ) R-> (0000.0) 0x38056d91 ???
--23913--     new: 0x04018e90 (strlen              ) R-> (2007.0) 0x04c2aa90 strlen
--23913-- REDIR: 0x4018e10 (ld-linux-x86-64.so.2:strcmp) redirected to 0x4c2bbe0 (strcmp)
--23913-- REDIR: 0x4019a00 (ld-linux-x86-64.so.2:mempcpy) redirected to 0x4c2ec20 (mempcpy)
--23913-- Reading syms from /usr/lib64/libcrypto.so.1.0.1e
--23913--    object doesn't have a symbol table
--23913-- Reading syms from /usr/lib64/libc-2.17.so
--23913-- Reading syms from /usr/lib64/libdl-2.17.so
--23913-- Reading syms from /usr/lib64/libz.so.1.2.7
--23913--    object doesn't have a symbol table
--23913-- REDIR: 0x52a6ec0 (libc.so.6:strcasecmp) redirected to 0x4a227b0 (_vgnU_ifunc_wrapper)
--23913-- REDIR: 0x52a3c40 (libc.so.6:strnlen) redirected to 0x4a227b0 (_vgnU_ifunc_wrapper)
--23913-- REDIR: 0x52a9190 (libc.so.6:strncasecmp) redirected to 0x4a227b0 (_vgnU_ifunc_wrapper)
--23913-- REDIR: 0x52a66a0 (libc.so.6:memset) redirected to 0x4a227b0 (_vgnU_ifunc_wrapper)
--23913-- REDIR: 0x52a6650 (libc.so.6:memcpy@GLIBC_2.2.5) redirected to 0x4a227b0 (_vgnU_ifunc_wrapper)
--23913-- REDIR: 0x52a20c0 (libc.so.6:strcmp) redirected to 0x4a227b0 (_vgnU_ifunc_wrapper)
--23913-- REDIR: 0x52a5630 (libc.so.6:__GI_strrchr) redirected to 0x4c2a450 (__GI_strrchr)
--23913-- REDIR: 0x52a3b60 (libc.so.6:__GI_strlen) redirected to 0x4c2a9f0 (__GI_strlen)
--23913-- REDIR: 0x5350570 (libc.so.6:__strcmp_sse42) redirected to 0x4c2bb90 (__strcmp_sse42)
--23913-- REDIR: 0x529cf70 (libc.so.6:malloc) redirected to 0x4c27b5c (malloc)
--23913-- REDIR: 0x52ad150 (libc.so.6:strchrnul) redirected to 0x4c2e740 (strchrnul)
--23913-- REDIR: 0x52a6870 (libc.so.6:__GI_mempcpy) redirected to 0x4c2e950 (__GI_mempcpy)
--23913-- REDIR: 0x529d370 (libc.so.6:free) redirected to 0x4c28c56 (free)
1 repeated 
==23913== 
==23913== HEAP SUMMARY:
==23913==     in use at exit: 0 bytes in 0 blocks
==23913==   total heap usage: 1 allocs, 1 frees, 750,000 bytes allocated
==23913== 
==23913== All heap blocks were freed -- no leaks are possible
==23913== 
==23913== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==23913== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
