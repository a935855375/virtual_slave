//
// Created by 孙川 on 2018/11/21.
//

#ifndef MYSQL_VIRTUAL_SLAVE_H
#define MYSQL_VIRTUAL_SLAVE_H
#include "mysql.h"
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include "mysqld_error.h"
//#include "log.h"



char* report_host = strdup("127.0.0.1");
char* report_password = strdup("ashe");
char* report_user = strdup("ashe");
uint report_port = 3239;
uint heartbeat_period = 15;
uint get_start_gtid_mode;
uint net_read_time_out;
int binlog_file_open_mode;
unsigned long long respond_pos;
unsigned long int re_connect_start_position;
char new_binlog_file_name[FN_REFLEN + 1];
bool recovery_mode;

char* master_uuid_old = 0;
char* master_uuid = 0;
char* master_uuid_new = 0;
bool switched;
char* virtual_slave_log_file;
int log_level;

int register_slave_on_master(MYSQL* mysql,bool *suppress_warnings);
int set_heartbeat_period(MYSQL* mysql);
int set_slave_uuid(MYSQL* mysql);
char* string_to_char(string str);
extern bool semi_sync_need_reply;

char* index_file_name = strdup("virtual_slave-bin.index");
File index_file_fd;

char* line_b = strdup("\n");
enum Exit_status {
    /** No error occurred and execution should continue. */
            OK_CONTINUE= 0,
    /** An error occurred and execution should stop. */
            ERROR_STOP,
    /** No error occurred but execution should stop. */
            OK_STOP
};


Exit_status determine_dump_mode();

Exit_status get_master_uuid();
Exit_status get_executed_gtid();
Exit_status set_gtid_executed();

Exit_status open_index_file();

Exit_status purge_binlog_file();

Exit_status search_last_file_position();

Exit_status like_reset_slave();
Exit_status prepare_log_file(char* );

#endif //MYSQL_VIRTUAL_SLAVE_H
