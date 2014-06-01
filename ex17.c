/*************************************************************************
	> File Name: ex17.c
	> Author: Lixin Yao
    */
    /*need to modify Database_load function*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//#define MAX_DATA 512
//#define MAX_ROWS 100

struct Address{
    int id;
    int set;
    char* name;
    char* email;
};
struct Database{
    struct Address* rows;
    int MAX_ROWS;
    int MAX_DATA;
};

struct Connection{
    FILE *file;
    struct Database *db;
};
 struct Connection conn;
void Database_close();
void die(const char* message)
{
    if (errno){
        perror(message);
    }
    else{
        printf("ERROR:%s\n",message);
    }
    Database_close();
    exit(1);
}
void Address_print(struct Address* addr)
{
    printf("%d %s %s\n",addr->id, addr->name, addr->email);
}

void Database_load()
{
    struct Database* db=conn.db;
    //int rc=fread(conn.db, sizeof(struct Database), 1, conn.file);
    //if (rc!=1) die("Failed to load database\n");
    int rc=fread(&db->MAX_ROWS, sizeof(int), 1, conn.file);
    if (rc!=1) die("fail to load db1\n");
    rc=fread(&db->MAX_DATA, sizeof(int), 1, conn.file);
    if (rc!=1) die("fail to load db2\n");
    int MAX_ROWS=db->MAX_ROWS;
    int MAX_DATA=db->MAX_DATA;
    db->rows=malloc(sizeof(struct Address)* MAX_ROWS);
    if (!db->rows) die("fail to load db7\n");
    int i;
    for (i=0;i<MAX_ROWS;i++)
    {
        rc=fread(&(db->rows[i].id), sizeof(int), 1, conn.file);
        if (rc!=1) die("failed to load db3\n");
      rc=fread(&db->rows[i].set, sizeof(int), 1, conn.file);
        if (rc!=1) die("failed to load db4\n");
// name and email are pointers already, need to malloc before assign
        db->rows[i].name = malloc(MAX_DATA);
        if (!db->rows[i].name)
        die("fail to load db8\n");
        rc=fread(db->rows[i].name, MAX_DATA, 1, conn.file);
        if (rc!=1) die("failed to load db5\n");

        db->rows[i].email = malloc(MAX_DATA);
        if (!db->rows[i].email)
        die("fail to load db9\n");
        rc=fread(db->rows[i].email, MAX_DATA, 1, conn.file);
        if (rc!=1) die("failed to load db6\n");
        
    }
    
}

void Database_write()
{
    struct Database* db=conn.db;
    rewind(conn.file);
    int MAX_ROWS=db->MAX_ROWS;
    int MAX_DATA=db->MAX_DATA;
    //int rc=fwrite(conn.db, sizeof(struct Database),1,conn.file);
    //if (rc!=1) die("Failed to write database\n");
    int rc=fwrite(&MAX_ROWS, sizeof(int), 1, conn.file);
    if (rc!=1) die("Failed to write database1\n");
    rc=fwrite(&MAX_DATA, sizeof(int), 1, conn.file);
    if (rc!=1) die("Failed to write database2\n");
    int i;
    for (i=0;i<MAX_ROWS;i++)
    {
        // could use pointer if not work
        rc=fwrite(&db->rows[i].id, sizeof(int), 1, conn.file);
        if (rc!=1) die("Failed to write database3\n");
        rc=fwrite(&db->rows[i].set, sizeof(int), 1, conn.file);
        if (rc!=1) die("Failed to write database4\n");
        rc=fwrite(db->rows[i].name, sizeof(char)*MAX_DATA, 1, conn.file);
    if (rc!=1) die("Failed to write database5\n");
        rc=fwrite(db->rows[i].email, sizeof(char)*MAX_DATA, 1, conn.file);
    if (rc!=1) die("Failed to write database6\n");
    }    
    if (fflush(conn.file)== -1)
    die("fail to flush db\n");
}
void Database_open(const char* filename, char mode)
{
    //db should be initialized/malloced before use
    conn.db=malloc(sizeof(struct Database));

    if (!conn.db) die("shit!");
    if (mode=='c'){
        conn.file=fopen(filename,"w");
    }
    else{
        conn.file=fopen(filename, "r+");

        if (conn.file)
            Database_load();
    }
    if (!conn.file) die("fail to open the file\n");
}

void Database_close()
{
    struct Database* db=conn.db;
        if (conn.file) fclose(conn.file);
        if (db) 
        {
            if (db->rows)
            {
                int i;
                for (i=0;i<db->MAX_ROWS;i++)
                {
                    struct Address* addr=&db->rows[i];
                    free(addr->name);
                    free(addr->email);
                }
                free(db->rows);
            }
            free(db);
        }
}


void Database_create( int MAX_ROWS, int MAX_DATA)
{
    int i;
    struct Database* db=conn.db;
    db->MAX_ROWS=MAX_ROWS;
    db->MAX_DATA=MAX_DATA;
    db->rows=malloc(sizeof(struct Address)*MAX_ROWS);
    //always remember to test after malloc 
    if (!db->rows) die("create error");
    for (i=0;i<MAX_ROWS;i++){
        //struct Address addr={.id=i, .set=0};
        struct Address* addr=&db->rows[i];
        addr->id=i; addr->set=0;
        addr->name=malloc(sizeof(char)*MAX_DATA);
        if (!addr->name) die("create error2");
        addr->name[0]='\0';// do not forget to initialize string pointer!!!!!!
        addr->email=malloc(sizeof(char)*MAX_DATA);
        if (!addr->email) die("create error3");
        addr->email[0]='\0';
    }
}

void Database_set( int id, const char* name, const char* email)
{
    struct Address* addr= &conn.db->rows[id];
    int MAX_DATA=conn.db->MAX_DATA;
    if (addr->set) die("already set. delete it first\n");
    addr->set=1;
    char *res=strncpy(addr->name, name,MAX_DATA);
    addr->name[MAX_DATA-1]='\0';
    if (!res) die("Name copy failed\n");
    res=strncpy(addr->email, email, MAX_DATA);
    addr->email[MAX_DATA-1]='\0';
    if (!res) die("email copy Failed\n");
}

void Database_get( int id)
{
    if (id>=conn.db->MAX_ROWS)
        die("index out of range\n");
    struct Address* addr=&conn.db->rows[id];
    if (addr->set){
        Address_print(addr);
    }
    else{
        die("id not exist\n");
    }
}

void Database_delete( int id)
{
   struct Database* db=conn.db;
    struct Address* addr=db->rows+id;
    addr->id=id; addr->set=0;
    memset(addr->name, '\0', db->MAX_DATA);
    memset(addr->email, '\0', db->MAX_DATA);

}
void Database_list()
{
    int i;
    struct Database* db=conn.db;
    for (i=0;i<db->MAX_ROWS;i++)
    {
        struct Address* cur=&db->rows[i];

        if (cur->set){
            Address_print(cur);
        }
    }
}
void  Database_find( char* cmd, char* arg)
{
    struct Database* db=conn.db;
        int MAX_ROWS=db->MAX_ROWS;
        int i;
    int done=0;
    if (!strcmp(cmd, "name"))
    {
        for (i=0;i<MAX_ROWS;i++)
        {
            if (db->rows[i].set)
            {
                if (!strcmp(db->rows[i].name, arg))
                {
                    Address_print(&db->rows[i]);
                    done=1;
                }
            }
        }
    }
    if (!strcmp(cmd, "email"))
    {
        for (i=0;i<MAX_ROWS;i++)
        {
            if (db->rows[i].set)
            {
                if (!strcmp(db->rows[i].email, arg))
                {
                    Address_print(&db->rows[i]);
                    done=1;
                }
            }
        }
    }
    if (!done) printf("not found\n");
}
int main(int argc, char* argv[])
{
    if (argc<3) die("<dbfile> <action> <action params>");

    char* filename=argv[1];
    char action=argv[2][0];
    Database_open(filename, action);
    int id=0;
    switch(action){
        case 'g':
        case 's':
        case 'd':
    if (argc>3) id=atoi(argv[3]);
    }
    //if (id>=MAX_ROWS) die("there are not that many records\n");

    switch(action){
        case 'c':
        if (argc!=5) die("wrong argument numbers\n");
        Database_create(atoi( argv[3]),atoi(argv[4]));
        Database_write();
        break;
        
        case 'g':
        if (argc!=4)  die("need an id to get\n");
        Database_get( id);
        break;

        case 's':
        if (argc!=6) die("need id, name email to set\n");

        Database_set( id, argv[4], argv[5]);
        Database_write();
        break;

        case 'd':
        if (argc!=4) die("need id to delete");
        Database_delete( id);
        Database_write();
        break;

        case 'l':
        printf("enter list test\n");
        Database_list();
        break;
        case 'f':
        if (argc!=5) die("not enough argument");
            Database_find( argv[3], argv[4]);
        break;
        default:
        die("invalid action\n");
    }
    Database_close();
    return 0;
}
