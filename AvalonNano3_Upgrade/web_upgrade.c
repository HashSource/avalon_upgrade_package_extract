void web_upgrade()
{
  __int64 v0; // s0
  __int64 thread; // a0

  if ( byte_44D863 )
  {
    v0 = 0LL;
    do
    {
      thread = get_thread(v0);
      if ( *(_BYTE *)(*(_QWORD *)(*(_QWORD *)(thread + 72) + 40LL) + v0 + 14177) )
      {
        *(_DWORD *)(thread + 120) = 1;
        if ( get_opt_log_level(thread) <= 40 )
          zlog(
            *(&strrchr - 24),
            "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/mmu/mmu.c",
            65LL,
            "web_upgrade",
            11LL,
            456LL,
            40LL,
            "web_upgrade");
      }
      else if ( get_opt_log_level(thread) <= 40 )
      {
        zlog(
          *(&strrchr - 24),
          "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/mmu/mmu.c",
          65LL,
          "web_upgrade",
          11LL,
          458LL,
          40LL,
          "Cannot connect to k210");
      }
      v0 = (int)v0 + 1;
    }
    while ( v0 < (unsigned __int8)byte_44D863 );
  }
}
