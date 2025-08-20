void __fastcall upgrade_load(__int64 a1, char *a2, _DWORD *a3)
{
  unsigned __int8 *http_param_value; // a0
  int v7; // a4
  unsigned __int64 v8; // a5
  int v9; // a5
  int v10; // a3
  unsigned __int64 v11; // a4
  unsigned __int8 v12; // a4
  unsigned __int64 v13; // a3
  unsigned __int8 v14; // a4
  unsigned __int64 v15; // a3
  unsigned __int8 v16; // a4
  unsigned __int64 v17; // a3
  unsigned __int8 v18; // a4
  unsigned __int64 v19; // a3
  unsigned __int8 v20; // a4
  unsigned __int64 v21; // a3
  unsigned __int8 v22; // a4
  unsigned __int64 v23; // a3
  unsigned int v24; // a2
  unsigned __int64 v25; // a3
  int v26; // a4
  __int64 v27; // a0
  char v28; // a5
  unsigned __int64 v29; // s4
  unsigned __int8 v30; // s4
  char v31; // a5
  unsigned __int64 v32; // a4
  char v33; // a5
  unsigned __int64 v34; // s5
  unsigned __int8 v35; // s5
  char v36; // a5
  unsigned __int64 v37; // a4
  char v38; // a4
  unsigned __int64 v39; // a5
  unsigned __int8 v40; // a5
  char v41; // a4
  unsigned __int64 v42; // a3
  char v43; // a3
  int v44; // a4
  unsigned __int64 v45; // a5
  unsigned __int8 v46; // a5
  char v47; // a3
  unsigned __int64 v48; // a2
  char v49; // a3
  int v50; // a5
  __int64 v51; // s8
  unsigned __int64 v52; // s7
  __int64 v53; // s6
  int v54; // s7
  char v55; // a5
  unsigned __int64 v56; // a4
  int v57; // a4
  unsigned __int64 v58; // a5
  __int64 v59; // a5
  int v60; // a3
  unsigned __int64 v61; // a4
  char v62; // a4
  unsigned __int64 v63; // a3
  char v64; // a4
  unsigned __int64 v65; // a3
  char v66; // a4
  unsigned __int64 v67; // a3
  char v68; // a4
  unsigned __int64 v69; // a3
  char v70; // a4
  unsigned __int64 v71; // a3
  char v72; // a4
  unsigned __int64 v73; // a3
  __int64 v74; // s3
  __int64 v75; // a0
  unsigned __int64 v76; // a3
  unsigned __int8 v77; // a4
  unsigned __int8 v78; // a4
  unsigned __int8 v79; // a5
  unsigned __int64 v80; // a2
  unsigned __int8 v81; // a3
  unsigned __int8 v82; // a4
  unsigned __int8 v83; // a5
  unsigned __int8 v84; // a4
  unsigned __int8 v85; // a5
  unsigned __int8 v86; // a4
  unsigned __int8 v87; // a5
  unsigned __int8 v88; // a3
  unsigned __int8 v89; // a4
  unsigned __int8 v90; // a2
  unsigned __int8 v91; // a3
  unsigned __int64 v92; // a3
  __int64 v93; // a4
  char v94[136]; // [sp+30h] [-88h] BYREF

  http_param_value = (unsigned __int8 *)get_http_param_value(a1, "begin");
  if ( http_param_value )
  {
    buf_offset = 0;
    v7 = *http_param_value;
    v8 = (unsigned __int8)(v7 - 48);
    if ( v8 <= 9 )
    {
      v10 = http_param_value[1];
      v9 = (_DWORD)v8 << 28;
      v11 = (unsigned __int8)(v10 - 48);
      if ( v11 <= 9 )
      {
LABEL_6:
        v9 |= (_DWORD)v11 << 24;
        goto LABEL_7;
      }
    }
    else
    {
      if ( (unsigned __int8)(v7 - 97) > 0x19uLL )
      {
        v25 = (unsigned __int8)(v7 - 65);
        v26 = (v7 - 55) << 28;
        v9 = 0;
        if ( v25 <= 0x19 )
          v9 = v26;
      }
      else
      {
        v9 = (v7 - 87) << 28;
      }
      v10 = http_param_value[1];
      v11 = (unsigned __int8)(v10 - 48);
      if ( v11 <= 9 )
        goto LABEL_6;
    }
    if ( (unsigned __int8)(v10 - 97) <= 0x19uLL )
    {
      v12 = http_param_value[2];
      v9 |= (v10 - 87) << 24;
      v13 = (unsigned __int8)(v12 - 48);
      if ( v13 <= 9 )
        goto LABEL_8;
      goto LABEL_26;
    }
    if ( (unsigned __int8)(v10 - 65) <= 0x19uLL )
      v9 |= (v10 - 55) << 24;
LABEL_7:
    v12 = http_param_value[2];
    v13 = (unsigned __int8)(v12 - 48);
    if ( v13 <= 9 )
    {
LABEL_8:
      v9 |= (_DWORD)v13 << 20;
      goto LABEL_9;
    }
LABEL_26:
    if ( (unsigned __int8)(v12 - 97) <= 0x19uLL )
    {
      v9 |= (unsigned __int8)(v12 - 87) << 20;
      v14 = http_param_value[3];
      v15 = (unsigned __int8)(v14 - 48);
      if ( v15 <= 9 )
        goto LABEL_10;
      goto LABEL_28;
    }
    if ( (unsigned __int8)(v12 - 65) <= 0x19uLL )
      v9 |= (unsigned __int8)(v12 - 55) << 20;
LABEL_9:
    v14 = http_param_value[3];
    v15 = (unsigned __int8)(v14 - 48);
    if ( v15 <= 9 )
    {
LABEL_10:
      v9 |= (_DWORD)v15 << 16;
      goto LABEL_11;
    }
LABEL_28:
    if ( (unsigned __int8)(v14 - 97) <= 0x19uLL )
    {
      v9 |= (unsigned __int8)(v14 - 87) << 16;
      v16 = http_param_value[4];
      v17 = (unsigned __int8)(v16 - 48);
      if ( v17 <= 9 )
        goto LABEL_12;
      goto LABEL_30;
    }
    if ( (unsigned __int8)(v14 - 65) <= 0x19uLL )
      v9 |= (unsigned __int8)(v14 - 55) << 16;
LABEL_11:
    v16 = http_param_value[4];
    v17 = (unsigned __int8)(v16 - 48);
    if ( v17 <= 9 )
    {
LABEL_12:
      v9 |= (_DWORD)v17 << 12;
      goto LABEL_13;
    }
LABEL_30:
    if ( (unsigned __int8)(v16 - 97) <= 0x19uLL )
    {
      v9 |= (unsigned __int8)(v16 - 87) << 12;
      v18 = http_param_value[5];
      v19 = (unsigned __int8)(v18 - 48);
      if ( v19 <= 9 )
        goto LABEL_14;
      goto LABEL_32;
    }
    if ( (unsigned __int8)(v16 - 65) <= 0x19uLL )
      v9 |= (unsigned __int8)(v16 - 55) << 12;
LABEL_13:
    v18 = http_param_value[5];
    v19 = (unsigned __int8)(v18 - 48);
    if ( v19 <= 9 )
    {
LABEL_14:
      v9 |= (_DWORD)v19 << 8;
      goto LABEL_15;
    }
LABEL_32:
    if ( (unsigned __int8)(v18 - 97) <= 0x19uLL )
    {
      v9 |= (unsigned __int8)(v18 - 87) << 8;
      v20 = http_param_value[6];
      v21 = (unsigned __int8)(v20 - 48);
      if ( v21 <= 9 )
        goto LABEL_16;
      goto LABEL_34;
    }
    if ( (unsigned __int8)(v18 - 65) <= 0x19uLL )
      v9 |= (unsigned __int8)(v18 - 55) << 8;
LABEL_15:
    v20 = http_param_value[6];
    v21 = (unsigned __int8)(v20 - 48);
    if ( v21 <= 9 )
    {
LABEL_16:
      v9 |= 16 * v21;
      goto LABEL_17;
    }
LABEL_34:
    if ( (unsigned __int8)(v20 - 97) <= 0x19uLL )
    {
      v9 |= 16 * (unsigned __int8)(v20 - 87);
      v22 = http_param_value[7];
      v23 = (unsigned __int8)(v22 - 48);
      if ( v23 <= 9 )
        goto LABEL_18;
      goto LABEL_36;
    }
    if ( (unsigned __int8)(v20 - 65) <= 0x19uLL )
      v9 |= 16 * (unsigned __int8)(v20 - 55);
LABEL_17:
    v22 = http_param_value[7];
    v23 = (unsigned __int8)(v22 - 48);
    if ( v23 <= 9 )
    {
LABEL_18:
      v9 |= v23;
      goto LABEL_19;
    }
LABEL_36:
    if ( (unsigned __int8)(v22 - 97) <= 0x19uLL )
    {
      total_len = v9 | (unsigned __int8)(v22 - 87);
      if ( get_opt_log_level(http_param_value) > 20 )
      {
LABEL_20:
        v24 = total_len;
        if ( (unsigned __int64)total_len > 0x1C0000 )
        {
LABEL_21:
          strcpy(a2, "ERR-0");
          *a3 = 5;
          return;
        }
LABEL_39:
        upgrade_buf = (__int64)&upgrate_buf;
        memset(&upgrate_buf, 255, v24);
        strcpy(a2, "OK");
        *a3 = 2;
        return;
      }
LABEL_38:
      zlog(
        *(&strrchr - 24),
        "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/web/cgi/cgi_misc.c",
        74LL,
        "upgrade_load",
        12LL,
        273LL,
        20LL,
        "\r\ntotal_len = %d\r\n",
        total_len);
      v24 = total_len;
      if ( (unsigned __int64)total_len > 0x1C0000 )
        goto LABEL_21;
      goto LABEL_39;
    }
    if ( (unsigned __int8)(v22 - 65) <= 0x19uLL )
      v9 |= (unsigned __int8)(v22 - 55);
LABEL_19:
    total_len = v9;
    if ( get_opt_log_level(http_param_value) > 20 )
      goto LABEL_20;
    goto LABEL_38;
  }
  v27 = get_http_param_value(a1, "uploadbtn");
  if ( v27 )
  {
    v28 = *(_BYTE *)v27;
    v29 = (unsigned __int8)(*(_BYTE *)v27 - 48);
    if ( v29 > 9 )
    {
      if ( (unsigned __int8)(v28 - 97) > 0x19uLL )
      {
        v82 = v28 - 65;
        v83 = 16 * (v28 - 55);
        v30 = 0;
        if ( v82 <= 0x19uLL )
          v30 = v83;
LABEL_62:
        v31 = *(_BYTE *)(v27 + 1);
        v32 = (unsigned __int8)(v31 - 48);
        if ( v32 > 9 )
        {
          if ( (unsigned __int8)(v31 - 97) > 0x19uLL )
          {
            v84 = v31 - 65;
            v85 = v30 | (v31 - 55);
            if ( v84 <= 0x19uLL )
              v30 = v85;
          }
          else
          {
            v30 |= v31 - 87;
          }
        }
        else
        {
          v30 |= v32;
        }
        v33 = *(_BYTE *)(v27 + 2);
        v34 = (unsigned __int8)(v33 - 48);
        if ( v34 > 9 )
        {
          if ( (unsigned __int8)(v33 - 97) > 0x19uLL )
          {
            v78 = v33 - 65;
            v79 = 16 * (v33 - 55);
            v35 = 0;
            if ( v78 <= 0x19uLL )
              v35 = v79;
LABEL_68:
            v36 = *(_BYTE *)(v27 + 3);
            v37 = (unsigned __int8)(v36 - 48);
            if ( v37 > 9 )
            {
              if ( (unsigned __int8)(v36 - 97) > 0x19uLL )
              {
                v86 = v36 - 65;
                v87 = v35 | (v36 - 55);
                if ( v86 <= 0x19uLL )
                  v35 = v87;
              }
              else
              {
                v35 |= v36 - 87;
              }
            }
            else
            {
              v35 |= v37;
            }
            v38 = *(_BYTE *)(v27 + 4);
            v39 = (unsigned __int8)(v38 - 48);
            if ( v39 > 9 )
            {
              if ( (unsigned __int8)(v38 - 97) > 0x19uLL )
              {
                v76 = (unsigned __int8)(v38 - 65);
                v77 = 16 * (v38 - 55);
                v40 = 0;
                if ( v76 <= 0x19 )
                  v40 = v77;
LABEL_74:
                v41 = *(_BYTE *)(v27 + 5);
                v42 = (unsigned __int8)(v41 - 48);
                if ( v42 > 9 )
                {
                  if ( (unsigned __int8)(v41 - 97) > 0x19uLL )
                  {
                    v88 = v41 - 65;
                    v89 = (v41 - 55) | v40;
                    if ( v88 <= 0x19uLL )
                      v40 = v89;
                  }
                  else
                  {
                    v40 |= v41 - 87;
                  }
                }
                else
                {
                  v40 |= v42;
                }
                v43 = *(_BYTE *)(v27 + 6);
                v44 = v40;
                v45 = (unsigned __int8)(v43 - 48);
                if ( v45 > 9 )
                {
                  if ( (unsigned __int8)(v43 - 97) > 0x19uLL )
                  {
                    v80 = (unsigned __int8)(v43 - 65);
                    v81 = 16 * (v43 - 55);
                    v46 = 0;
                    if ( v80 <= 0x19 )
                      v46 = v81;
                    goto LABEL_80;
                  }
                  LOBYTE(v45) = v43 - 87;
                }
                v46 = 16 * v45;
LABEL_80:
                v47 = *(_BYTE *)(v27 + 7);
                v48 = (unsigned __int8)(v47 - 48);
                if ( v48 > 9 )
                {
                  if ( (unsigned __int8)(v47 - 97) > 0x19uLL )
                  {
                    v90 = v47 - 65;
                    v91 = (v47 - 55) | v46;
                    if ( v90 <= 0x19uLL )
                      v46 = v91;
                  }
                  else
                  {
                    v46 |= v47 - 87;
                  }
                }
                else
                {
                  v46 |= v48;
                }
                v49 = *(_BYTE *)(v27 + 8);
                v50 = v46 | (v44 << 8);
                v51 = v50;
                v52 = (unsigned __int8)(v49 - 48);
                v53 = v50;
                if ( v52 > 9 )
                {
                  if ( (unsigned __int8)(v49 - 97) <= 0x19uLL )
                  {
                    v54 = 16 * (unsigned __int8)(v49 - 87);
                  }
                  else
                  {
                    v54 = 0;
                    if ( (unsigned __int8)(v49 - 65) <= 0x19uLL )
                      v54 = 16 * (unsigned __int8)(v49 - 55);
                  }
                }
                else
                {
                  v54 = 16 * v52;
                }
                v55 = *(_BYTE *)(v27 + 9);
                v56 = (unsigned __int8)(v55 - 48);
                if ( v56 > 9 )
                {
                  if ( (unsigned __int8)(v55 - 97) <= 0x19uLL )
                  {
                    v54 |= (unsigned __int8)(v55 - 87);
                  }
                  else if ( (unsigned __int8)(v55 - 65) <= 0x19uLL )
                  {
                    v54 |= (unsigned __int8)(v55 - 55);
                  }
                }
                else
                {
                  v54 |= v56;
                }
                v57 = *(unsigned __int8 *)(v27 + 10);
                v58 = (unsigned __int8)(v57 - 48);
                if ( v58 > 9 )
                {
                  if ( (unsigned __int8)(v57 - 97) > 0x19uLL )
                  {
                    v92 = (unsigned __int8)(v57 - 65);
                    v93 = (v57 - 55) << 28;
                    v59 = 0LL;
                    if ( v92 <= 0x19 )
                      v59 = v93;
                  }
                  else
                  {
                    v59 = (v57 - 87) << 28;
                  }
                }
                else
                {
                  v59 = (int)((_DWORD)v58 << 28);
                }
                v60 = *(unsigned __int8 *)(v27 + 11);
                v61 = (unsigned __int8)(v60 - 48);
                if ( v61 > 9 )
                {
                  if ( (unsigned __int8)(v60 - 97) <= 0x19uLL )
                  {
                    v59 |= (v60 - 87) << 24;
                  }
                  else if ( (unsigned __int8)(v60 - 65) <= 0x19uLL )
                  {
                    v59 |= (v60 - 55) << 24;
                  }
                }
                else
                {
                  v59 |= (int)((_DWORD)v61 << 24);
                }
                v62 = *(_BYTE *)(v27 + 12);
                v63 = (unsigned __int8)(v62 - 48);
                if ( v63 > 9 )
                {
                  if ( (unsigned __int8)(v62 - 97) <= 0x19uLL )
                  {
                    v59 |= (unsigned __int8)(v62 - 87) << 20;
                  }
                  else if ( (unsigned __int8)(v62 - 65) <= 0x19uLL )
                  {
                    v59 |= (unsigned __int8)(v62 - 55) << 20;
                  }
                }
                else
                {
                  v59 |= v63 << 20;
                }
                v64 = *(_BYTE *)(v27 + 13);
                v65 = (unsigned __int8)(v64 - 48);
                if ( v65 > 9 )
                {
                  if ( (unsigned __int8)(v64 - 97) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | ((unsigned __int8)(v64 - 87) << 16));
                  }
                  else if ( (unsigned __int8)(v64 - 65) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | ((unsigned __int8)(v64 - 55) << 16));
                  }
                }
                else
                {
                  v59 |= v65 << 16;
                }
                v66 = *(_BYTE *)(v27 + 14);
                v67 = (unsigned __int8)(v66 - 48);
                if ( v67 > 9 )
                {
                  if ( (unsigned __int8)(v66 - 97) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | ((unsigned __int8)(v66 - 87) << 12));
                  }
                  else if ( (unsigned __int8)(v66 - 65) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | ((unsigned __int8)(v66 - 55) << 12));
                  }
                }
                else
                {
                  v59 |= v67 << 12;
                }
                v68 = *(_BYTE *)(v27 + 15);
                v69 = (unsigned __int8)(v68 - 48);
                if ( v69 > 9 )
                {
                  if ( (unsigned __int8)(v68 - 97) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | ((unsigned __int8)(v68 - 87) << 8));
                  }
                  else if ( (unsigned __int8)(v68 - 65) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | ((unsigned __int8)(v68 - 55) << 8));
                  }
                }
                else
                {
                  v59 |= v69 << 8;
                }
                v70 = *(_BYTE *)(v27 + 16);
                v71 = (unsigned __int8)(v70 - 48);
                if ( v71 > 9 )
                {
                  if ( (unsigned __int8)(v70 - 97) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | (16 * (unsigned __int8)(v70 - 87)));
                  }
                  else if ( (unsigned __int8)(v70 - 65) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | (16 * (unsigned __int8)(v70 - 55)));
                  }
                }
                else
                {
                  v59 |= 16 * v71;
                }
                v72 = *(_BYTE *)(v27 + 17);
                v73 = (unsigned __int8)(v72 - 48);
                if ( v73 > 9 )
                {
                  if ( (unsigned __int8)(v72 - 97) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | (unsigned __int8)(v72 - 87));
                  }
                  else if ( (unsigned __int8)(v72 - 65) <= 0x19uLL )
                  {
                    v59 = (int)(v59 | (unsigned __int8)(v72 - 55));
                  }
                }
                else
                {
                  v59 |= v73;
                }
                if ( buf_offset == v59
                  && (v74 = v27 + 18, 2 * v53 == strlen((const char *)(v27 + 18)))
                  && total_len - (int)v53 >= (unsigned __int64)buf_offset )
                {
                  hex2bin(upgrade_buf + (unsigned int)buf_offset, v74, v51);
                  buf_offset += v53;
                  sprintf(a2, "%s%08x", "OK", buf_offset);
                  *a3 = 10;
                }
                else
                {
                  v75 = sprintf(a2, "%s%08x", "ERR-1-", buf_offset);
                  *a3 = 14;
                  if ( get_opt_log_level(v75) <= 80 )
                    zlog(
                      *(&strrchr - 24),
                      "/home/wangjunshuai/workspace/heater/k230_sdk/app_heater/web/cgi/cgi_misc.c",
                      74LL,
                      "upgrade_load",
                      12LL,
                      302LL,
                      80LL,
                      "upgrade pkg err,num(%d),len(%d),offset(%d),total(%d),repeat(%d)",
                      (v30 << 8) | v35,
                      v53,
                      buf_offset,
                      total_len,
                      v54);
                }
                return;
              }
              LOBYTE(v39) = v38 - 87;
            }
            v40 = 16 * v39;
            goto LABEL_74;
          }
          LOBYTE(v34) = v33 - 87;
        }
        v35 = 16 * v34;
        goto LABEL_68;
      }
      LOBYTE(v29) = v28 - 87;
    }
    v30 = 16 * v29;
    goto LABEL_62;
  }
  if ( get_http_param_value(a1, &off_15D238) || buf_offset >= (unsigned __int64)total_len && total_len )
  {
    memset(v94, 0, 0x80uLL);
    upgrade_aup(upgrade_buf, v94);
    web_upgrade();
    total_len = 0;
  }
}
