char *__fastcall set_avalon_device_upgrade(__int64 a1, __int64 a2, char *a3)
{
  __int64 v3; // a3
  char *v4; // s0
  __int64 v6; // a3
  void *v9; // a0

  v3 = *(int *)(a1 + 192);
  v4 = a3;
  if ( v3 > 0 )
  {
    _A5 = *(_QWORD *)(a1 + 200);
    if ( *(_DWORD *)(*(_QWORD *)_A5 + 120LL) == 1LL )
    {
LABEL_6:
      if ( get_opt_log_level(a1) <= 80 )
        zlog(
          *(&strrchr - 24),
          "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
          81LL,
          "set_avalon_device_upgrade",
          25LL,
          3507LL,
          80LL,
          "The last upgrade was not completed");
      strcpy(v4, "The last upgrade was not completed");
      return v4;
    }
    v6 = _A5 + 8LL * (unsigned int)(v3 - 1);
    while ( _A5 != v6 )
    {
      __asm { th.ldib         a4, 8(a5) }
      if ( *(_DWORD *)(_A4 + 120) == 1LL )
        goto LABEL_6;
    }
  }
  if ( *(_BYTE *)(*(_QWORD *)(a1 + 40) + 14177LL) )
  {
    set_avalon_upgrade();
    return 0LL;
  }
  else
  {
    v9 = memcpy(a3, "Cannot connect to k210", 0x17uLL);
    if ( get_opt_log_level(v9) <= 80 )
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "set_avalon_device_upgrade",
        25LL,
        3520LL,
        80LL,
        "%s",
        v4);
  }
  return v4;
}
