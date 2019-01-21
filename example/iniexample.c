#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "iniparser.h"

void create_example_ini_file(void);
int  parse_ini_file(char * ini_name);

int main(int argc, char * argv[])
{
    int     status ;

    if (argc<2) {
        create_example_ini_file();
        status = parse_ini_file("example.ini");
    } else {
        status = parse_ini_file(argv[1]);
    }
    return status ;
}
char * getkeyvalue(const char *section, const char *key,  char *val, const char* ini_name){
    dictionary  *   ini ;

    /* Some temporary variables to hold query results */

    const char  *   s ;
    char str[255] = {0};
    ini = iniparser_load(ini_name);
    if (ini==NULL) {
        fprintf(stderr, "cannot parse file: %s %s\n", ini_name, __func__);
        return "" ;
    }
    sprintf(str, ":%s:%s", section, key);
    s = iniparser_getstring(ini, str, NULL);
    if(s)
        strcpy(val , s);
    iniparser_freedict(ini);
    return val;
}
int setkeyvalue(const char *section,const char *key, const char *val, const char *ini_name ){
    dictionary  *   dic ;
    FILE    *   ini ;
    /* Some temporary variables to hold query results */

    const char  *   s ;
    char str[255] = {0};
    dic = iniparser_load(ini_name);
    if (dic==NULL) {
        fprintf(stderr, "cannot parse file: %s %s\n", ini_name, __func__);
        dic = dictionary_new(2);
    }
    sprintf(str, "%s:%s", section, key);

    if ((ini=fopen(ini_name, "w"))==NULL) {
        fprintf(stderr, "iniparser: cannot create example.ini\n");
        goto End ;
    }    
    dictionary_set(dic, str,val);
    iniparser_dump(dic, ini);

    fclose(ini);
  End:  
    iniparser_freedict(dic);
    return 0;
}
void save_ini_file( dictionary  *   dic, const char *sec){
    FILE    *   ini ;

    if ((ini=fopen("example.ini", "w"))==NULL) {
        fprintf(stderr, "iniparser: cannot create example.ini\n");
        return ;
    }    
    iniparser_dump_ini(dic, ini);
    fclose(ini);
}
void create_example_ini_file(void)
{
    FILE    *   ini ;

    if ((ini=fopen("example.ini", "w"))==NULL) {
        fprintf(stderr, "iniparser: cannot create example.ini\n");
        return ;
    }

    fprintf(ini,
    "#\n"
    "# This is an example of ini file\n"
    "#\n"
    "\n"
    "[Pizza]\n"
    "\n"
    "Ham       = yes ;\n"
    "Mushrooms = TRUE ;\n"
    "Capres    = 0 ;\n"
    "Cheese    = Non ;\n"
    "\n"
    "\n"
    "[Wine]\n"
    "\n"
    "Grape     = Cabernet Sauvignon ;\n"
    "Year      = 1989 ;\n"
    "Country   = Spain ;\n"
    "Alcohol   = 12.5  ;\n"
    "\n");
    fclose(ini);
}


int parse_ini_file(char * ini_name)
{
    dictionary  *   ini ;
    char buf[255]={0};
    /* Some temporary variables to hold query results */
    int             b ;
    int             i ;
    double          d ;
    const char  *   s ;

    // ini = iniparser_load(ini_name);
    // if (ini==NULL) {
    //     ini = dictionary_new(2);
    //     fprintf(stderr, "cannot parse file: %s %s\n", ini_name, __func__);
    // //    return -1 ;
    // }
  //  iniparser_dump(ini, stderr);

    setkeyvalue("menu","author", "xxx", ini_name);
    s = getkeyvalue("menu", "author", buf,ini_name);
    printf("author:  [%s]\n", s ? s : "UNDEF");
    return 0;
    /* Get pizza attributes */
    printf("Pizza:\n");

    b = iniparser_getboolean(ini, "pizza:ham", -1);
    printf("Ham:       [%d]\n", b);
    b = iniparser_getboolean(ini, "pizza:mushrooms", -1);
    printf("Mushrooms: [%d]\n", b);
    b = iniparser_getboolean(ini, "pizza:capres", -1);
    printf("Capres:    [%d]\n", b);
    b = iniparser_getboolean(ini, "pizza:cheese", -1);
    printf("Cheese:    [%d]\n", b);

    /* Get wine attributes */
    printf("Wine:\n");
    s = iniparser_getstring(ini, "wine:grape", NULL);
    printf("Grape:     [%s]\n", s ? s : "UNDEF");

    i = iniparser_getint(ini, "wine:year", -1);
    printf("Year:      [%d]\n", i);

    s = iniparser_getstring(ini, "wine:country", NULL);
    printf("Country:   [%s]\n", s ? s : "UNDEF");

    d = iniparser_getdouble(ini, "wine:alcohol", -1.0);
    printf("Alcohol:   [%g]\n", d);

    s = iniparser_getstring(ini, ":menu:author", NULL);
    printf("author:     [%s]\n", s ? s : "UNDEF");

    dictionary_set(ini, "menu:author","aaa");
    dictionary_set(ini, "menu:author","bbb");
    save_ini_file(ini,"menu");
    iniparser_freedict(ini);
    return 0 ;
}


