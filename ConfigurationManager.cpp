static uint8 ScanConfig(char* str, ...)
{ CB(14120)
   uint8 cnt=0;			// number of arguments counter
   uint8 fmt_pos = 1;
   uint16 pos;
   uint16 n;
   char tmp[20];
   va_list  argp;
   uint32 arg;
   uint16* aOutP;  // Arg out pointer
   char *fmt;

   va_start( argp, str);
   fmt = va_arg(argp, char*);  // get format string

   for (pos=0; pos<strlen(str); )
   { CB(14121)
      for (;str[pos]==' '; pos++)
      { CB(14122)
         //skip blanks
      }
      if (str[pos]==0)  // Null char, EOL
      { CB(14123)
         break;
      }
      for (n=0;str[pos]!=' ' && str[pos]!=0; pos++, n++) // get next arg
      { CB(14124)
         tmp[n] = str[pos];
      }
      tmp[n]=0;

      arg = va_arg(argp, int);  // get next output argument pointer

      if (fmt[fmt_pos]=='d')    // Decimal
      { CB(14125)
         aOutP = (uint16*)arg;
         (*aOutP) = atoi(tmp);
      }
      else if (fmt[fmt_pos]=='o')  // Octal
      { CB(14126)
         uint16 oNum=0;
         for (n=0; n<strlen(tmp);n++)  //atoo
         { CB(14127)
            oNum = oNum*8 + tmp[n] - '0';
         }
         aOutP = (uint16*)arg;
         (*aOutP) = oNum;

      }
      else if (fmt[fmt_pos]=='c')  // Character
      { CB(14128)
         char* cOutP = (char*)arg;
         (*cOutP) = tmp[0];
      }
      else //assume string
      { CB(14129)
         strcpy((char*)arg, tmp);
      }
      fmt_pos+=2;   // pass current format type and "%"
      cnt++;
      if (cnt==10 || fmt_pos > strlen(fmt))
      { CB(14130)
         break; //no more than 10 args
      }
   }
   va_end(argp);

   return cnt;
}
