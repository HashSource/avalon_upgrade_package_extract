void avalonnano_trig_upgrade()
{
  FILE *v0; // a0
  FILE *v1; // s3
  int v2; // s0
  void *v3; // a0
  void *v4; // s4
  __int64 v6; // a0
  __int64 devices; // a0
  __int64 v9; // s0
  __int64 v11; // s1
  __int64 v12; // a0
  __int64 v13; // a5
  struct stat v14[2]; // [sp+0h] [-188h] BYREF

  if ( stat("/data/upgrade_aup", v14) != -1LL )
  {
    v0 = fopen("/data/upgrade_aup", "rb");
    v1 = v0;
    if ( v0 )
    {
      fseek(v0, 0LL, 2);
      v2 = ftell(v1);
      rewind(v1);
      v3 = malloc(v2);
      v4 = v3;
      if ( v3 )
      {
        fread(v3, 1uLL, v2, v1);
        if ( total_devices > 0LL )
        {
          _S2 = 0LL;
          v6 = 0LL;
          do
          {
            devices = get_devices(v6);
            _A5 = *(_QWORD *)(devices + 200);
            v9 = devices;
            __asm { th.lrd          a5, a5, s2, 3 }
            if ( *(_DWORD *)(_A5 + 120) == 1LL )
              break;
            v11 = *(_QWORD *)(devices + 40) + 12288LL;
            if ( upgrade_aup((__int64)v4, (char *)&v14[0].__unused[1]) )
              break;
            if ( !*(_BYTE *)(v11 + 1889) )
            {
              fclose(v1);
              free(v4);
              if ( get_opt_log_level(v12) <= 80 )
                zlog(
                  *(&strrchr - 24),
                  "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/cgminer/driver-avalon12.c",
                  81LL,
                  "avalonnano_trig_upgrade",
                  23LL,
                  3582LL,
                  80LL,
                  "Cannot connect to k210");
              return;
            }
            v13 = total_devices;
            v6 = (int)++_S2;
            *(_DWORD *)(**(_QWORD **)(v9 + 200) + 120LL) = 1;
          }
          while ( (int)_S2 < v13 );
        }
        fclose(v1);
        free(v4);
      }
      else
      {
        fclose(v1);
      }
    }
  }
}
