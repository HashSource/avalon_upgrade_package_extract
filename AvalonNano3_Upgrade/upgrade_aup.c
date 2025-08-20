__int64 __fastcall upgrade_aup(__int64 a1, char *a2)
{
  __int64 opt_log_level; // a0
  __int64 v5; // a0
  __int64 v6; // a0
  __int64 v7; // s5
  int v9; // a5
  __int64 v12; // s3
  const char *v13; // s7
  unsigned __int64 v14; // s0
  unsigned __int64 v15; // s2
  unsigned __int64 v16; // s6
  __int64 v17; // a0
  unsigned __int64 v18; // s0
  unsigned __int64 v19; // a5
  const char *v20; // s6
  __int64 v21; // a0
  unsigned int v22; // s0
  int v23; // s2
  const void *v24; // s1
  __int64 v25; // a0
  int v26; // s3
  __int64 v27; // a0
  int v28; // s3
  __int64 v29; // a0
  int v30; // s3
  __int64 v31; // a0
  __int64 v32; // a0
  __int64 v33; // a0
  __int64 v34; // a0
  __int64 v35; // a0
  __int64 v36; // a0
  _DWORD v37[4]; // [sp+28h] [-10h] BYREF

  _S1 = a1;
  opt_log_level = get_opt_log_level(a1);
  if ( opt_log_level <= 100 )
    opt_log_level = zlog(
                      *(&strrchr - 24),
                      "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
                      81LL,
                      "upgrade_aup",
                      11LL,
                      3324LL,
                      100LL,
                      (const char *)&off_155230,
                      _S1);
  v5 = get_opt_log_level(opt_log_level);
  if ( v5 <= 100 )
    v5 = zlog(
           *(&strrchr - 24),
           "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
           81LL,
           "upgrade_aup",
           11LL,
           3325LL,
           100LL,
           (const char *)&off_155238,
           *(int *)(_S1 + 16));
  if ( *(_QWORD *)_S1 == 0x6D726F6620505541LL && *(_WORD *)(_S1 + 8) == 29793LL )
  {
    v7 = 0LL;
    if ( get_opt_log_level(v5) <= 80 )
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "upgrade_aup",
        11LL,
        3336LL,
        80LL,
        "AUP format version: %d",
        *(_DWORD *)(_S1 + 16));
    v9 = *(_DWORD *)(_S1 + 96);
    _A2 = 32 * (*(_DWORD *)(_S1 + 92) + v9) + 100;
    __asm { th.lurwu        s0, s1, a2, 0 }
    v12 = (unsigned int)(32 * (*(_DWORD *)(_S1 + 92) + v9) + 100);
    if ( _S0 == crc32(0LL, _S1) )
    {
      v13 = (const char *)(_S1 + 100);
      v14 = 0LL;
      if ( !*(_DWORD *)(_S1 + 92) )
        goto LABEL_44;
      while ( 1 )
      {
        v17 = dev_super_get();
        v16 = v14;
        v14 = (int)v14 + 1;
        if ( !strncmp((const char *)(v17 + 124), v13, 0x20uLL) )
          break;
        v15 = *(int *)(_S1 + 92);
        v16 = v14;
        v13 += 32;
        if ( v14 >= v15 )
          goto LABEL_21;
      }
      if ( get_opt_log_level(0LL) <= 80 )
        zlog(
          *(&strrchr - 24),
          "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
          81LL,
          "upgrade_aup",
          11LL,
          3349LL,
          80LL,
          "Hardware %s is supported by AUP",
          v13);
      v15 = *(int *)(_S1 + 92);
LABEL_21:
      if ( v16 == v15 )
      {
LABEL_44:
        v35 = sprintf(a2, "Err%02d: AUP is NOT for this hardware! This hardware is %s", 8, "MM4v1_X3");
        if ( get_opt_log_level(v35) <= 100 )
          zlog(
            *(&strrchr - 24),
            "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
            81LL,
            "upgrade_aup",
            11LL,
            3356LL,
            100LL,
            "%s",
            a2);
      }
      else
      {
        v18 = v15;
        v19 = *(_DWORD *)(_S1 + 96) + (int)v15;
        if ( v15 < v19 )
        {
          v20 = (const char *)(32 * (int)v15 + 100LL + _S1);
          while ( 1 )
          {
            v21 = dev_super_get();
            v15 = v18;
            v18 = (int)v18 + 1;
            if ( !strncmp((const char *)(v21 + 188), v20, 0x20uLL) )
              break;
            v15 = v18;
            v20 += 32;
            v19 = *(_DWORD *)(_S1 + 92) + *(_DWORD *)(_S1 + 96);
            if ( v18 >= v19 )
              goto LABEL_29;
          }
          if ( get_opt_log_level(0LL) <= 80 )
            zlog(
              *(&strrchr - 24),
              "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
              81LL,
              "upgrade_aup",
              11LL,
              3362LL,
              80LL,
              "Software %s is supported by AUP",
              v20);
          v19 = *(_DWORD *)(_S1 + 92) + *(_DWORD *)(_S1 + 96);
        }
LABEL_29:
        if ( v15 == v19 )
        {
          v33 = sprintf(a2, "Err%02d: AUP is NOT for this software! This software is %s", 8, "MM318_X2");
          if ( get_opt_log_level(v33) <= 100 )
            zlog(
              *(&strrchr - 24),
              "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
              81LL,
              "upgrade_aup",
              11LL,
              3368LL,
              100LL,
              "%s",
              a2);
        }
        else
        {
          v22 = *(_DWORD *)(_S1 + 20);
          v23 = *(_DWORD *)(_S1 + 88);
          v24 = (const void *)(_S1 + v12 + 4);
          if ( v23 == crc32(0LL, v24) )
          {
            v37[0] = 0;
            v25 = crc32(0LL, v24);
            v26 = v25;
            if ( get_opt_log_level(v25) <= 80 )
              zlog(
                *(&strrchr - 24),
                "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
                81LL,
                "upgrade_aup",
                11LL,
                3384LL,
                80LL,
                "aup_crc32 = 0x%x  aup_payload_crc = 0x%x aup_payload_len = %d",
                v26,
                v23,
                v22);
            v37[0] = v26;
            v27 = open("/opt/upgrade_aup", 577, 420LL);
            v28 = v27;
            if ( v27 == -1 )
            {
              v34 = sprintf(a2, "Err%02d: Open File Failed ", 8);
              if ( get_opt_log_level(v34) <= 100 )
                zlog(
                  *(&strrchr - 24),
                  "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
                  81LL,
                  "upgrade_aup",
                  11LL,
                  3392LL,
                  100LL,
                  "%s",
                  a2);
            }
            else
            {
              write(v27, v37, 4uLL);
              close(v28);
              v29 = open("/opt/upgrade_aup", 1025);
              v30 = v29;
              if ( v29 != -1 )
              {
                write(v29, v24, v22);
                close(v30);
                return v7;
              }
              v36 = sprintf(a2, "Err%02d: Open File Failed ", 8);
              if ( get_opt_log_level(v36) <= 100 )
                zlog(
                  *(&strrchr - 24),
                  "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
                  81LL,
                  "upgrade_aup",
                  11LL,
                  3401LL,
                  100LL,
                  "%s",
                  a2);
            }
          }
          else
          {
            v31 = sprintf(a2, "Err%02d: AUP Checksum of payload failed", 8);
            if ( get_opt_log_level(v31) <= 100 )
              zlog(
                *(&strrchr - 24),
                "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
                81LL,
                "upgrade_aup",
                11LL,
                3377LL,
                100LL,
                "%s",
                a2);
          }
        }
      }
    }
    else
    {
      v32 = sprintf(a2, "Err%02d: AUP Checksum of header failed", 8);
      if ( get_opt_log_level(v32) <= 100 )
        zlog(
          *(&strrchr - 24),
          "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
          81LL,
          "upgrade_aup",
          11LL,
          3342LL,
          100LL,
          "%s",
          a2);
    }
  }
  else
  {
    v6 = sprintf(a2, "Err%02d: AUP file header error", 8);
    if ( get_opt_log_level(v6) <= 100 )
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
        81LL,
        "upgrade_aup",
        11LL,
        3331LL,
        100LL,
        "%s",
        a2);
  }
  return 8LL;
}
