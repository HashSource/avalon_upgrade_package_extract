__int64 __fastcall upgrade_send_data(__int64 a1)
{
  int v1; // a4
  __int64 v2; // a0
  int v3; // s11
  __int64 v4; // s6
  size_t v5; // s7
  size_t v6; // s0
  __int16 v7; // s1
  __int64 v8; // s5
  __int64 v9; // s0
  __int64 v10; // a0
  __int64 v11; // a0
  __int64 v12; // s1
  __int64 v13; // s0
  __int64 opt_log_level; // a0
  int v16; // [sp+8h] [-280h]
  int v17; // [sp+28h] [-260h]
  __off_t v18; // [sp+48h] [-240h]
  int v19; // [sp+50h] [-238h]
  _BYTE v21[128]; // [sp+60h] [-228h] BYREF
  struct stat v22; // [sp+E0h] [-1A8h] BYREF
  _BYTE v23[4]; // [sp+1F0h] [-98h] BYREF
  unsigned __int8 v24; // [sp+1F4h] [-94h]
  char v25; // [sp+1FCh] [-8Ch]

  if ( stat("/opt/upgrade_aup", &v22) == -1LL )
    return -1LL;
  v1 = (unsigned __int16)(v22.st_size / 128);
  if ( (unsigned __int16)(v22.st_size % 128) )
    v1 = (unsigned __int16)(v22.st_size / 128 + 1);
  v18 = v22.st_size % 128;
  v19 = (unsigned __int16)(v22.st_size % 128);
  v17 = v1;
  v2 = open("/opt/upgrade_aup", 0);
  v3 = v2;
  if ( v2 == -1 )
    return -1LL;
  if ( v17 )
  {
    v4 = 0LL;
    v5 = 128LL;
    while ( 2 )
    {
      memset(v21, 0, v5);
      v6 = v5;
      lseek(v3, (int)v4 * (int)v5, 0);
      v7 = v5;
      if ( v17 - 1 == v4 )
      {
        v7 = v19;
        v5 = v19;
        v6 = (unsigned __int16)v18;
      }
      read(v3, v21, v6);
      LOWORD(v22.__unused[1]) = 20035;
      WORD2(v22.__unused[1]) = 144;
      LOWORD(v22.__unused[2]) = v17;
      HIWORD(v22.__unused[1]) = v4;
      WORD1(v22.__unused[2]) = v7;
      memcpy((char *)&v22.__unused[2] + 4, v21, v6);
      WORD1(v22.__unused[1]) = crc16((char *)&v22.__unused[1] + 4, v5 + 8);
      LODWORD(v8) = 5;
LABEL_10:
      LODWORD(v9) = 4;
      while ( 1 )
      {
        data_toast_send(&v22.__unused[1]);
        v10 = data_toast_receive(v23, 200LL);
        if ( !v10 )
          break;
        if ( get_opt_log_level(v10) > 80 )
        {
          v9 = (int)v9 - 1;
          if ( v9 == -1 )
            goto LABEL_15;
        }
        else
        {
          v16 = v9;
          v9 = (int)v9 - 1;
          zlog(
            *(&strrchr - 24),
            &byte_154000 - 344,
            81LL,
            "avalonnano_xfer_pkg",
            19LL,
            820LL,
            80LL,
            "send type=0x%X, retry idx=%d, interval=%d",
            BYTE4(v22.__unused[1]),
            v16,
            200);
          if ( v9 == -1 )
            goto LABEL_15;
        }
      }
      if ( v24 == 145LL )
      {
        memset(&v22.__unused[1], 0, v5 + 8);
        cgsleep_ms(1LL);
        v4 = (int)v4 + 1;
        if ( v4 != v17 )
          continue;
        goto LABEL_20;
      }
      break;
    }
LABEL_15:
    v8 = (int)v8 - 1;
    v11 = cgsleep_ms(1LL);
    if ( v8 )
      goto LABEL_10;
    if ( get_opt_log_level(v11) <= 80 )
    {
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "upgrade_send_data",
        17LL,
        3274LL,
        80LL,
        "k230 send msg count > 5");
      return -1LL;
    }
    return -1LL;
  }
LABEL_20:
  LOWORD(v22.__unused[1]) = 20035;
  WORD2(v22.__unused[1]) = 144;
  HIWORD(v22.__unused[1]) = v17;
  LODWORD(v22.__unused[2]) = (unsigned __int16)v17;
  WORD1(v22.__unused[1]) = crc16((char *)&v22.__unused[1] + 4, 8LL);
  LODWORD(v13) = 4;
  while ( 1 )
  {
    data_toast_send(&v22.__unused[1]);
    opt_log_level = data_toast_receive(v23, 200LL);
    v12 = opt_log_level;
    if ( !opt_log_level )
      break;
    opt_log_level = get_opt_log_level(opt_log_level);
    if ( opt_log_level <= 80 )
      opt_log_level = zlog(
                        *(&strrchr - 24),
                        &byte_154000 - 344,
                        81LL,
                        &aIdDResultCgmin[-1864],
                        19LL,
                        820LL,
                        80LL,
                        "send type=0x%X, retry idx=%d, interval=%d",
                        BYTE4(v22.__unused[1]),
                        v13,
                        200);
    v13 = (int)v13 - 1;
    if ( v13 == -1 )
      goto LABEL_34;
  }
  if ( v24 != 145LL || v25 != 1LL )
  {
    LODWORD(v13) = 0;
LABEL_34:
    if ( get_opt_log_level(opt_log_level) <= 80 )
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "upgrade_send_data",
        17LL,
        3294LL,
        80LL,
        "%s-%d: AVANANO_P_UPGRADE: recv xfer data with err %d",
        *(const char **)(*(_QWORD *)(a1 + 8) + 16LL),
        *(_DWORD *)(a1 + 16),
        v13);
    close(v3);
    return -1LL;
  }
  if ( get_opt_log_level(0LL) <= 80 )
    zlog(
      *(&strrchr - 24),
      "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
      81LL,
      "upgrade_send_data",
      17LL,
      3292LL,
      80LL,
      "k210 crc16 verfity ok");
  close(v3);
  return v12;
}
