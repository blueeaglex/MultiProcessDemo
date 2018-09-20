#include "Base/os.h"
#include <string>
#include <vector>

#include <sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<syslog.h>
#include<iostream>
#include<limits>
#include<stdio.h>
//void daemonize(const char *cmd)
//{
//    int         i, fd0, fd1, fd2;
//    pid_t           pid;
//    struct rlimit       rl;
//    struct sigaction    sa;
//
//    umask(0);   // Clear file creation mask.
//
//    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)  {   // Get maximum number of file descriptors.
//        err_quit("%s: can't get file limit", cmd);
//    }
//    if ((pid = fork()) < 0)  {  //这一步fork保证进程不是进程组组长进程
//        err_quit("%s: can't fork", cmd);
//    }
//    else if (pid != 0) {    /* parent */
//        exit(0);
//    }
//    setsid();  // 创建一个回话，会话只包含子进程，且子进程是会话首进程
//    /*
//    会话首进程的退出会出发SIGHUP信号
//    默认此信号的操作会终止进程
//     */
//    sa.sa_handler = SIG_IGN;
//    sigemptyset(&sa.sa_mask);
//    sa.sa_flags = 0;
//    if (sigaction(SIGHUP, &sa, NULL) < 0)  {
//        err_quit("%s: can't ignore SIGHUP", cmd);
//    }
//    /*
//    再次创建子进程，退出父进程，保证守护进程不是会话首进程，这样open的时候就不会被分配终端
//    */
//    if ((pid = fork()) < 0)  {
//        err_quit("%s: can't fork", cmd);
//    }
//    else if (pid != 0) {  /* parent */
//        exit(0);
//    }
//
//    if (chdir("/") < 0)   {  // 改变当前工作路径为根目录
//        err_quit("%s: can't change directory to /", cmd);
//    }
//    if (rl.rlim_max == RLIM_INFINITY)   {  //关闭所有打开的文件描述符
//        rl.rlim_max = 1024;
//    }
//    for (i = 0; i < rl.rlim_max; i++)    {
//        close(i);
//    }
//    /*
//     因为前面关闭了所有的文件描述符，此时open返回的必定是最小的0，后面两次dup返回的依次是1、2，
//     也就完成了对标准输入、标准输出、标准错误重定向至/dev/null的操作
//     */
//    fd0 = open("/dev/null", O_RDWR);
//    fd1 = dup(0);
//    fd2 = dup(0);
//
//    /*
//     * Initialize the log file.
//     */
//    openlog(cmd, LOG_CONS, LOG_DAEMON);
//    if (fd0 != 0 || fd1 != 1 || fd2 != 2)
//    {
//        syslog(LOG_ERR, "unexpected file descriptors %d %d %d",fd0, fd1, fd2);
//        exit(1);
//    }
//}


//using namespace boost::process;
using namespace os::process;

int main()
{
    std::cout << "APP Path:" << os::filesystem::current_path() << std::endl;
    if(daemon(1,1) < 0)
        std::cout << "Failed to launch daemon" << std::endl;
    else
        std::cout << "Running as daemon!" << std::endl;
    auto file = fopen("daemon_output.txt","wb");
    fprintf(file,"This is the daemon!!");
    fclose(file);

restart:
    ipstream pipe_stream;
    //child c("gcc --version", std_out > pipe_stream);
    child c("gedit");
    //std::system("");
    std::string line;

    //while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
    //   std::cerr << line << std::endl;
    //c.wait();

    while(c.running())
    {
        sleep(1);
        std::cout <<"Daemon is running" << c.id() << std::endl;
    }

    if(c.running() == false)
    {
        std::cout <<"Child ID:" << c.id() << std::endl;
        goto restart;
    }
}

