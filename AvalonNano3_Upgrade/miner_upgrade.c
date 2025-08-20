void __fastcall __noreturn miner_upgrade(int *a1)
{
  __int64 v2; // a0
  __int64 v3; // s1
  __int64 v4; // s3
  __int64 thread; // s0
  __int64 v6; // s11
  __int64 v7; // a0
  __int64 v8; // a0
  int v10; // [sp+0h] [-28h]
  int v11; // [sp+8h] [-20h]

  _S2 = *a1;
  while ( 1 )
  {
    v2 = sem_wait(&stru_44D840);
    if ( get_opt_log_level(v2) <= 40 )
      break;
    while ( 1 )
    {
      if ( _S2 <= 0 )
      {
LABEL_16:
        if ( _S2 )
          break;
        goto LABEL_14;
      }
LABEL_4:
      v3 = 0LL;
      v4 = 0LL;
      do
      {
        thread = get_thread(v3);
        LODWORD(v6) = 5;
        while ( 1 )
        {
          v6 = (int)v6 - 1;
          v7 = avalonnano_upgrade(*(_QWORD *)(thread + 72));
          if ( !v7 )
            break;
          if ( !v6 )
            goto LABEL_8;
        }
        v4 = (int)v4 + 1;
LABEL_8:
        if ( *(_DWORD *)(*(_QWORD *)(thread + 72) + 64LL) != 1LL )
        {
          *(_DWORD *)(thread + 120) = 0;
          if ( get_opt_log_level(v7) <= 40 )
            zlog(
              *(&strrchr - 24),
              "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/mmu/mmu.c",
              65LL,
              &aTimerCreate_0[-2032],
              13LL,
              485LL,
              40LL,
              "Pushing sem post to thread %d",
              *(_DWORD *)thread);
          cgsem_post(
            thread + 24,
            "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/mmu/mmu.c",
            &aTimerCreate_0[-2032],
            486LL);
        }
        v3 = (int)v3 + 1;
      }
      while ( _S2 != v3 );
      if ( _S2 != v4 )
        break;
LABEL_14:
      system("killall -USR1 miner_upgrade_post.sh");
      v8 = sem_wait(&stru_44D840);
      if ( get_opt_log_level(v8) <= 40 )
        goto LABEL_15;
    }
    system("killall -USR2 miner_upgrade_post.sh");
  }
LABEL_15:
  _A5 = *a1;
  __asm { th.sdd          s2, a5, (sp) }
  zlog(
    *(&strrchr - 24),
    "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/mmu/mmu.c",
    65LL,
    &aTimerCreate_0[-2032],
    13LL,
    469LL,
    40LL,
    "receive miner update sem miners=%d--%d",
    v10,
    v11);
  if ( _S2 <= 0 )
    goto LABEL_16;
  goto LABEL_4;
}
