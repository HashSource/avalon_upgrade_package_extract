char *__fastcall set_avalon_upgrade(__int64 a1, const char *a2, char *a3)
{
  unsigned __int64 v6; // s2
  unsigned int v7; // s4
  size_t v8; // a0
  char *v9; // a3
  int v10; // a5
  unsigned __int64 v11; // a4
  char *result; // a0
  __int64 v13; // a2
  __int64 v17; // a0
  __int64 v18; // a0
  char *v19; // a0
  __int64 v20; // a0
  __int64 v21; // a0
  __int64 v22; // a0
  __int64 v23; // a0
  unsigned __int8 v24; // [sp+10h] [-28h] BYREF
  unsigned __int8 v25; // [sp+11h] [-27h]
  int v26; // [sp+18h] [-20h]
  unsigned int v27; // [sp+24h] [-14h]
  int v28; // [sp+28h] [-10h]
  unsigned __int16 v29; // [sp+2Ch] [-Ch]

  hex2bin(&v24, a2, 32LL);
  if ( v24 != 2LL )
  {
    v18 = sprintf(a3, "Err%02d: API version mismatch: %x (%x)", 1, v24, 2);
    if ( get_opt_log_level(v18) <= 20 )
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "set_avalon_upgrade",
        18LL,
        3434LL,
        20LL,
        "%s",
        a3);
    return a3;
  }
  if ( v25 != 30LL )
  {
    v17 = sprintf(a3, "Err%02d: header size mismatch: %x (%x)", 2, v25, 30);
    if ( get_opt_log_level(v17) <= 20 )
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "set_avalon_upgrade",
        18LL,
        3440LL,
        20LL,
        "%s",
        a3);
    return a3;
  }
  v6 = v28;
  v7 = v27;
  if ( (int)v27 < (unsigned __int64)v28 )
  {
    v21 = sprintf(a3, "Err%02d: offset (%x) is larger than file size (%x)", 4, v28, v27);
    if ( get_opt_log_level(v21) <= 20 )
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "set_avalon_upgrade",
        18LL,
        3447LL,
        20LL,
        "%s",
        a3);
    return a3;
  }
  v8 = strlen(a2);
  if ( v8 - 64 < v29 )
  {
    v22 = sprintf(a3, "Err%02d: payload length (%x) is larger than param (%lx)", 5, v29, (v8 >> 1) - 32);
    if ( get_opt_log_level(v22) <= 20 )
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "set_avalon_upgrade",
        18LL,
        3454LL,
        20LL,
        "%s",
        a3);
    return a3;
  }
  v9 = (char *)aup_buf_20;
  if ( !aup_buf_20 )
  {
    aup_buf_20 = (__int64)malloc(v27);
    v9 = (char *)aup_buf_20;
    if ( !aup_buf_20 )
    {
      v23 = sprintf(a3, "Err%02d: Malloc AUP Buf Failed", 6);
      if ( get_opt_log_level(v23) <= 100 )
        zlog(
          *(&strrchr - 24),
          "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
          81LL,
          "set_avalon_upgrade",
          18LL,
          3461LL,
          100LL,
          "%s",
          a3);
      return a3;
    }
  }
  v10 = uid_cur_19;
  if ( v26 == (__int64)uid_cur_19 )
  {
    v11 = offset_next_18;
  }
  else
  {
    v19 = (char *)memset(v9, 255, v7);
    v10 = v26;
    v6 = v28;
    v9 = v19;
    offset_next_18 = 0;
    uid_cur_19 = v26;
    v11 = 0LL;
  }
  if ( v11 < v6 )
  {
    v20 = sprintf(a3, "Err%02d: offset (%x) is not expected (%x), uid:%d", 4, v6, v11, v10);
    if ( get_opt_log_level(v20) <= 20 )
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "set_avalon_upgrade",
        18LL,
        3473LL,
        20LL,
        "%s",
        a3);
    return a3;
  }
  hex2bin(&v9[(unsigned int)v6], a2 + 64, v29);
  result = 0LL;
  offset_next_18 = v28 + v29;
  if ( v27 == (__int64)(v28 + v29) )
  {
    if ( upgrade_aup(aup_buf_20, a3) )
    {
      strcpy(a3, "upgrade failed");
      free((void *)aup_buf_20);
      result = a3;
      aup_buf_20 = 0LL;
    }
    else
    {
      v13 = *(int *)(a1 + 192);
      if ( v13 > 0 )
      {
        _A0 = *(_QWORD *)(a1 + 200);
        _A5 = 0LL;
        do
        {
          __asm { th.lrd          a3, a0, a5, 3 }
          ++_A5;
          *(_DWORD *)(_A3 + 120) = 1;
        }
        while ( (int)_A5 < v13 );
      }
      free((void *)aup_buf_20);
      result = 0LL;
      aup_buf_20 = 0LL;
    }
  }
  return result;
}
