// This is the C++ Sorce code for computer matchmaking. The program can be
// modified by editing this code and then recompiling it.


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <cctype>

char *strlwr(char *s) {
  char *p = s;
  while ((*p = tolower(*p)))
    p++;
  return s;
}

#define db_siz 600
#define an_siz 400

int db_rec;
int proc_num;
char fil_db[79], fil_out[79], fil_hdr[79];
struct datatype {
  char ln[20], fn[20], gr[11], sx[2], an[30];
} db[db_siz];
struct anstype {
  int nu;
  float pe;
} an[an_siz];

void process(int n) {
  FILE *hdr, *prn;
  int i, j, k, m, t, y;
  unsigned char c, d, e;
  char s[79], z[80];

  for (i = 0; i <= an_siz; i++) { // an[0] is temp for xfer
    an[i].nu = 0;
    an[i].pe = 0.0;
  }
  k = strlen(db[n].an);
  t = 0;
  // o=sizeof(db[n].an);
  for (i = 1; i < db_rec; i++) {
    m = 0;
    if (db[i].sx[0] != db[n].sx[0]) {
      for (j = 0; j <= k; j++) {
        if (db[i].an[j] == db[n].an[j])
          m++;
      }
      t++;
      an[t].nu = i; // v---increase percentage
      an[t].pe = (((float)m / (float)k) * 100) * .4 + 60; // range from 60%-100%
    }
  }
  for (i = 1; i <= t; i++) { // other sort
    for (j = i + 1; j <= t; j++) {
      if (an[i].pe < an[j].pe) {
        an[0].nu = an[i].nu;
        an[0].pe = an[i].pe;
        an[i].nu = an[j].nu;
        an[i].pe = an[j].pe;
        an[j].nu = an[0].nu;
        an[j].pe = an[0].pe;
      }
    }
  }
  while ((prn = fopen(fil_out, "ab")) == NULL) {
    std::cout << "Error: Unable to open output file: " << fil_out
              << "\nEnter file for output: ";
    // cin >> fil_out;
    gets(fil_out);
    if (fil_out == NULL)
      break; // <---------- return 3; ????????
  }
  while ((hdr = fopen(fil_hdr, "rb")) == NULL) {
    std::cout << "Error: Unable to open header file: " << fil_hdr
              << "\nEnter file to use as header file: ";
    // cin >> fil_hdr;
    gets(fil_out);
    if (fil_hdr == NULL)
      break; // <----------- return 4; ????????
  }
  i = -1;
  y = 0;
  while (!feof(hdr)) {
    c = fgetc(hdr);
    if (c == '`') {
      j = 0;
      d = fgetc(hdr);
      if (d == 'N') {
        j++;
        i++;
        if (i == 0) {
          strcpy(s, db[n].fn);
          strcat(s, " ");
          strcat(s, db[n].ln);
        } else {
          strcpy(s, db[an[i].nu].fn);
          strcat(s, " ");
          strcat(s, db[an[i].nu].ln);
        }
        fputs(s, prn);
      }
      if (d == 'G') {
        j++;
        if (i == 0) {
          strcpy(s, db[n].gr);
        } else {
          strcpy(s, db[an[i].nu].gr);
        }
        fputs(s, prn);
      }
      if ((d == 'P') && (i > 0)) {
        j++;
        sprintf(s, "%3.1f%%", an[i].pe);
        fputs(s, prn);
      }
      if (d == 'A') {
        j++;
        y++;
        strcpy(s, db[an[y].nu].fn);
        strcat(s, " ");
        strcat(s, db[an[y].nu].ln);
        sprintf(z, "%-26s %-8s           %3.1f%% \n", s, db[an[y].nu].gr,
                an[y].pe);
        fputs(z, prn);
      }
      if (j == 0) {
        fputc(c, prn);
        ungetc(d, hdr);
      }
    } else {
      fputc(c, prn);
    }
  }
  fclose(prn);
  fclose(hdr);
}

int main(void) {
  FILE *stream;
  char s[79], t[79], u[79], v[79], w[79];
  int i, j, k;
  char *p, *q;

  std::cout << "Computer Matchmaking\n";
  std::cout << "CCC Technology Club (1997-2008)\n";
  std::cout << "Original program by Mark Marano\n";
  std::cout << "Revisions by George Burri\n";
  std::cout << "This build compiled on 1/20/08\n";
  std::cout << "Refer to the Readme for instructions\n";
  std::cout << "\n";
  if ((stream = fopen("Settings.txt", "rt")) == NULL) {
    std::cout << "Error: Cannot open Settings.txt\n\n";
    std::cout << "This file must exist in the same directory as compter "
                 "matchmaking.exe\n";
    std::cout << "and contain the following format:\n\n";
    std::cout << "  File to read records from (comma-deliminated ascii file)\n";
    std::cout << "  File for output\n";
    std::cout << "  Header filename\n";
    std::cout << "  Number of records to proccess\n";
    std::cout << "\nexample:\n";
    std::cout << "  Database.txt\n";
    std::cout << "  Results.txt\n";
    std::cout << "  Header.txt\n";
    std::cout << "  0\n";
    std::cout << "\nheader file must contain contain formatting to be printed "
                 "correctly;\n";
    std::cout
        << "`N will be replaced with the person's name, `G with their grade;\n";
    std::cout << "any `N `G `P there-on-after will be replaced with "
                 "name/grade/percentage of match\n";
    if (getchar() == 0)
      getchar();
    return 1;
  }
  fgets(fil_db, 79, stream);
  j = strlen(fil_db);
  fil_db[j - 1] = '\0';
  std::cout << "DB: " << fil_db << std::endl;

  fgets(fil_out, 79, stream);
  j = strlen(fil_out);
  fil_out[j - 1] = '\0';
  fgets(fil_hdr, 79, stream);
  j = strlen(fil_hdr);
  fil_hdr[j - 1] = '\0';
  fgets(s, 79, stream);
  proc_num = atoi(s);
  fclose(stream); // cfg file
  while ((stream = fopen(fil_db, "rt")) == NULL) {
    std::cout << "Error: Unable to open " << fil_db << " for input" << std::endl;
    std::cout << "Enter comma-deliminated ascii database file: ";
    std::cin >> fil_db;
    //gets(fil_db);
    if (fil_db == NULL) {
      return 2;
    }
  }
  i = 0;
  while (!feof(stream)) {
    i++;
    fgets(s, 127, stream);

    p = strtok(s, ",");
    strcpy(db[i].ln, p); // WARNING: If the database is empty, the program will
                         // crash while trying to access db[i].ln
    p = strtok(NULL, ",");
    strcpy(db[i].fn, p);
    p = strtok(NULL, ",");
    strcpy(db[i].gr, p);
    p = strtok(NULL, ",");
    strcpy(db[i].sx, p);
    p = strtok(NULL, ",");
    strcpy(db[i].an, p);
    j = strlen(db[i].an) - 1;
    if (db[i].an[j] == '\n')
      db[i].an[j] = '\0';
  }
  db_rec = i;
  fclose(stream); // db file
  std::cout << db_rec << " record(s) read\n";
  while (1) {
    std::cout << "process [Enter . for menu]: ";
    // cin >> s;
    gets(s);
    if ((!strncasecmp(s, "q", sizeof(s))) ||
        (!strncasecmp(s, "quit", sizeof(s))) ||
        (!strncasecmp(s, "x", sizeof(s))) ||
        (!strncasecmp(s, "exit", sizeof(s)))) {
      return 0;
    }
    if (s[0] == '.') {
      memset(s, 0, sizeof(s));
      while ((0 != strncasecmp(s, "q", sizeof(s))) &&
             (0 != strncasecmp(s, "quit", sizeof(s)))) {
        std::cout << "Menu [Enter ? for help]: ";
        // cin >> s;
        gets(s);
        if (s[0] == '?') {
          std::cout << " Syntax for process is #-#,#,#-#\n";
          std::cout << " examples:\n  1-200,250-300,305\n    processes records "
                       "1-200, skips 201-249, processes 250-300, and 305\n";
          std::cout << " Hit [q]uit or e[x]it at process menu to quit\n\n";
          std::cout << "Menu commands available:\n";
          std::cout << " [d]isp - display current settings\n";
          std::cout << " [l]ist - lists all records\n";
          std::cout << " [n]umber - change number to process\n";
          std::cout << " [o]ut - changes output device\n";
          std::cout << " [s]earch - searches records\n";
          std::cout << " [q]uit - quits to process menu\n";

          std::cout << "\nRefer to the Readme for more information\n";
        }
        if ((!strncasecmp(s, "d", sizeof(s))) ||
            (!strncasecmp(s, "disp", sizeof(s)))) {
          std::cout << " Ascii database file: " << fil_db << "\n";
          std::cout << " Output file: " << fil_out << "\n";
          std::cout << " Header file: " << fil_hdr << "\n";
          std::cout << " Number to process: " << proc_num << "\n";
        }
        if ((!strncasecmp(s, "o", sizeof(s))) ||
            (!strncasecmp(s, "out", sizeof(s)))) {
          std::cout << "Enter new output file: ";
          // cin >> fil_out;
          gets(fil_out);
        }
        if ((!strncasecmp(s, "n", sizeof(s))) ||
            (!strncasecmp(s, "number", sizeof(s)))) {
          std::cout << "Enter number to process [0 for all]: ";
          // cin >> proc_num;
          gets(t);
          proc_num = atoi(t);
        }
        if ((!strncasecmp(s, "l", sizeof(s))) ||
            (!strncasecmp(s, "list", sizeof(s)))) {
          for (i = 1; i <= db_rec; i++) {
            std::cout << i << ". " << db[i].fn << " " << db[i].ln << " ["
                      << db[i].gr << "/" << db[i].sx << "]\n";
            if (!(i % 20)) {
              if (getchar() == 27)
                i = db_rec + 1;
              std::cout << "\n";
            }
          }
        }
        if ((!strncasecmp(s, "s", sizeof(s))) ||
            (!strncasecmp(s, "search", sizeof(s)))) {
          std::cout << "Enter search string: ";
          // cin >> s;
          gets(s);
          strlwr(s);
          i = 0;
          for (j = 1; j <= db_rec; j++) {
            k = 0;
            strcpy(v, db[j].fn);
            strlwr(v);
            strcpy(w, db[j].ln);
            strlwr(w);
            if (strstr(w, s) != NULL)
              k++;
            if (strstr(v, s) != NULL)
              k++;
            strcpy(t, v);
            strcat(t, " ");
            strcat(t, w);
            if (strstr(t, s) != NULL)
              k++;
            strcpy(t, w);
            strcat(t, ", ");
            strcat(t, v);
            if (strstr(t, s) != NULL)
              k++;
            if (k > 0) {
              i++;
              if (i == 1)
                std::cout << " matches found:\n";
              std::cout << "  " << j << ". " << db[j].fn << " " << db[j].ln
                        << "  [" << db[j].gr << "/" << db[j].sx << "]\n";
              if (!(i % 20)) {
                if (getchar() == 27)
                  j = db_rec + 1;
                std::cout << "\n";
              }
            }
          }
          if (i == 0)
            std::cout << " No matches found\n";
        }
      }
    } else {
      p = strtok(s, ",");
      strcpy(t, s);
      while (t[0] != '\0') {
        if ((q = strchr(t, '-')) == NULL) {
          j = atoi(t);
          process(j);
          if (p != NULL)
            std::cout << ".";
        } else {
          // strset(u,'\0'); for(j=0;j<(int)q;j++) u[j]=t[j]; j=atoi(u);
          // i=strlen(t);strset(u,'\0'); for(k=(int)q;k<i;k++) u[k-(int)q]=t[k];
          // k=atoi(u);
          k = strlen(t);
          j = 0;
          // strset(u,'\0');
          // strset(v,'\0');
          memset(u, 0, sizeof(u));
          memset(v, 0, sizeof(v));

          for (i = 1; i <= k; i++) {
            if (t[i - 1] == '-') {
              j = i;
            } else {
              if (!j) {
                u[i - 1] = t[i - 1];
                // u++;
              } else {
                v[i - j - 1] = t[i - 1];
                // v++;
              }
            }
          }
          j = atoi(u);
          k = atoi(v);
          for (i = j; i <= k; i++) {
            process(i);
            std::cout << ".";
          }
        }
        if (p == NULL)
          break;
        if ((p = strtok(NULL, ",")) == NULL) {
          t[0] = '\0';
        } else {
          strcpy(t, p);
        }
      }
    }
  }
}
