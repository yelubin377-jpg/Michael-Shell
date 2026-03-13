#define _POSIX_C_SOURCE 200809L //指定遵循POSIX 2008的标准，有更多的函数和宏可以使用不出歧义
#include <stdio.h>
// printf - 打印输出到终端

//fgets（存储，大小，输入） ----->  读取用户输入的命令
//(存储读到内容的数组/指针，读取的最大字符数，输入流（终端输入固定写成stdin）)
//即eg:fgets(line,100,stdin);把终端输入丢到line数组里。
//成功返回存储数组的指针
//失败等返回NULL


// perror("打开文件失败") ------> 打印错误信息
// if(fd<0)
// {
//   perror("打开文件失败"); //输出：打开文件失败：No such file or directory
// }
// 防背刺专用：系统调用失败时用来定位问题的


// fflush(stdout) -----> 强制将缓冲区内容丢到终端
// 补充亿下：终端输出（stdout）
// 一般来说，丢个 fflush(stdout); 在那就行，把提示符直接丢到终端显示
// 成功返回 0
// 失败返回 EOF（即 -1）
// 重要：不刷新的话用户可能看不到提示符，会被误以为程序卡死了



#include <stdlib.h>
// strdup(另外一个字符串数组) --->  把另一个字符串数组的内容整过来 plus 版，不用手动开辟内存，但要记得释放内存
// 自动 malloc，然后拷贝字符串
// char *str = "哈基米";
// char *dst = strdup(str);
// printf("%s\n",dst);
// free(dst);
// 注意：用完记得 free()，不然内存泄漏警告！

// exit(0);正常退出 - 世界和平，大家散场
// exit(1);异常退出（非 0 都是） - 出事了，赶紧跑


#include <string.h>//---->字符串操作头文件

//strlen

//strcmp(字符串1,字符串2) ---> 比较两个字符串
//相等返回0
//不等返回非0
//eg:  strcmp(cmd , "cd") == 0;康康是不是内建命令


// strncpy(存储，输入，大小)； ----> 字符串拷贝，与 strdup 差不多，但是要注意别被 '\0' 背刺。
// 高能预警：如果源字符串太长，目标数组可能没有'\0'结尾，使用时小心崩渍！


#include <unistd.h>
// getcwd(存储目录的字符数组，大小) //读取当前目录，即在哪
// 成功返回数组指针
// 失败返回 NULL
// 防坑提示：数组一定要够大，不然会溢出！


// chdir(路径名) ------> 切换目录的路径名 (就是 cd 这个路径名)
// 成功返回 0
// 失败返回 -1 并设置 errno（错误代码）
// 常见翻车现场：路径不存在、没权限访问


// fork(); ----> 创建子进程 一分为二的魔法
// 成功：父进程中返回所创建的子进程的 PID 
//      子进程中返回 0 
// 失败：返回 -1 - 创建失败，洗洗睡吧
// 注意：fork 之后两个进程同时运行，代码从 fork 处继续执行


// pipe(int pipefd[2])  ----> 创建管道，实现进程间通信
// 进一步解释:int pipefd[2]:一个大小为 2 的整数数组
// 这两个整数分别为：pipefd[0] ---> 成为管道读取端的文件描述符
//                 pipefd[1] ---> 成为管道写入端的文件描述符
// 成功返回 0
// 失败返回 -1
// 注意"进程分裂" - fork 之前建管道，不然每个子进程都有自己的管道
// 形象理解：就像一根水管，一头进水（写），一头出水（读）


// dup2(已经打开的文件描述符，新的文件描述符) ---> 实现< , > ,  2>&1   ,  实现文件描述符的复制和重定向
// 成功返回 newfd 
// 失败返回 -1



//close(文件描述符（一个int数）)

#include <sys/types.h> //系统数据类型头文件 
//pid_t
//pid_t pid = fork(); --->定义进程ID变量，接受fork的返回值


//fd_t  --->文件描述符类型

#include <sys/wait.h>// 等待子进程头文件
// waitpid(子进程 ID,status[&存子进程状态的整数 (需要特定解码器读取)]，0)  ----> 处理僵尸进程
// 表示等待子进程结束并且记录其退出状态
// 为什么要等？防止子进程变成僵尸进程占着位置



// WIFEXITED(status)  ---> 解码器 1（wifexited)
// 检查子进程是否正常终止（如子进程调用了 return 或 exit(0)）
// 若是正常终止，返回真（非 0 值）
// 若是被杀死（SIGSEGV、SIGKILL），返回 0
// 使用顺序：先用这个，确定正常退出了再用下一个




// EXITSTATUS(status) ---> 解码器 2（wexitstatus）--> 必须在解码器 1 结束后使用
//  专门用来从 status 中提取退出码



#include <signal.h>
// 先举几个栗子：
// SIGINT  --->  CTRL + C - 用户想中断你
// SIGQUIT --->  会生成 core，类似上面，但是一般调试用 - 调试专用
// SIGTERM --->  优雅退出信号 - 礼貌地让你走
// SIGKILL --->  强制杀死信号 - 给爷4   （美伊和谈这一块）

// SIG_DFL --->  恢复系统默认处理方式 - 爱咋咋地
// SIG_IGN --->  忽略这个信号，假装没看到   --->  signal(SIGINT,SIG_IGN); - 我当没听见



//该头文件一般用法 -- signal(信号类型，执行函数);



#include <fcntl.h>
// open - 打开文件的利器  
// O_RDONLY 只读 - 只能看不能写
// O_WRONLY 只写 - 只能写不能看
// O_CREAT  没有文件就创造文件 - 无中生有
// O_APPEND 追加 - 在文件末尾接着写
// O_TRUNC  有文件就清空文件 - 除旧迎新

#include <errno.h>
// 提供 errno  全局错误码变量，系统函数失败时自动赋值（与 perror 配合来的）
// 使用场景：函数返回 -1 时，errno 会告诉你具体啥错了
#include <limits.h>
// PATH_MAX --->  系统最大路径长度 - 路径再长也不能超过这个
// INT_MAX --->   整形最大值 - int 的天花板
// eg 栗子：char path[PATH_MAX]  --> perhaps 会更兼容一点
#define MAX_CMD_LEN 4096
#define MAX_ARGS 64
#define MAX_PIPELINE 16
#define MAX_PATH_LEN 4096

typedef struct 
{
    char *args[MAX_ARGS];
    int argc;
    char *input_file;
    char *output_file;
    int append_mode;
} Command;

typedef struct 
{
    Command cmds[MAX_PIPELINE];
    int cmd_count;
    int background;  // 注意！！！background 属于整个 pipeline，而不是单个 command
} Pipeline;

static char last_dir[MAX_PATH_LEN] = {0};

// 函数前向声明
void free_command(Command *cmd);
void free_pipeline(Pipeline *pipeline);

//处理将是进程
// SIGCHLD 信号处理函数：自动回收后台子进程，防止僵尸进程
// 使用 WNOHANG 非阻塞等待，回收所有已结束的子进程
// 【注意】信号处理函数中只能调用 async-signal-safe 函数
void sigchld_handler(int sig)
{
    (void)sig;  // 消除未使用参数警告
    int saved_errno = errno;  // 保存 errno，防止被信号处理破坏
    // 循环回收所有已结束的子进程
    while (waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;  // 恢复 errno
}

// Shell 初始化函数
// 功能：设置信号处理和保存初始目录
void init_shell(void)
{
    // 重要！！！使用 sigaction 替代 signal，行为更可控、跨平台更一致
    struct sigaction sa_ignore, sa_child;
    
    // 忽略 SIGINT (Ctrl+C) 和 SIGQUIT (Ctrl+\)
    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGINT, &sa_ignore, NULL);
    sigaction(SIGQUIT, &sa_ignore, NULL);
    
    // 设置 SIGCHLD handler 回收后台子进程
    // SA_RESTART: 自动重启被信号中断的系统调用
    // SA_NOCLDSTOP: 子进程 stop 时不发 SIGCHLD
    sa_child.sa_handler = sigchld_handler;
    sigemptyset(&sa_child.sa_mask);
    sa_child.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa_child, NULL);
    
    // 获取并保存当前工作目录，用于后续 cd - 功能 
    if (getcwd(last_dir, sizeof(last_dir)) == NULL) 
    {
        perror("getcwd");
        exit(1);
    }
}

// 打印 Shell 提示符
// 功能：显示彩色的用户、主机名和路径信息，如: user@hostname:~ $
void print_prompt(void)
{
    char cwd[MAX_PATH_LEN];
    char display_path[MAX_PATH_LEN];
    char hostname[256] = "localhost";
    
    // 获取用户名
    const char *user = getenv("USER");
    if (!user) user = "user";
    
    // 获取主机名
    gethostname(hostname, sizeof(hostname));
    
    // 尝试获取当前工作目录并显示彩色提示符 
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        // 尝试将 HOME 目录替换为 ~，更像真实 shell
        char *home = getenv("HOME");
        if (home && strncmp(cwd, home, strlen(home)) == 0) 
        {
            snprintf(display_path, sizeof(display_path), "~%s", cwd + strlen(home));
        } 
        else 
        {
            strncpy(display_path, cwd, sizeof(display_path) - 1);
            display_path[sizeof(display_path) - 1] = '\0';
        }
        
        // 更像 bash 的提示符：user@hostname:path $
        printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m $ ", user, hostname, display_path);
        fflush(stdout);
    } else 
    {
        printf("$ ");
        fflush(stdout);
    }
}

// 去除字符串首尾空白字符
// str 待处理的字符串
// return 处理后的字符串指针 (原地修改)
char *trim(char *str)
{
    // 跳过开头的空格和制表符 - 前面的不要
    while (*str == ' ' || *str == '\t') str++;
    
    // 防背刺：如果是空字符串，直接返回
    size_t len = strlen(str);
    if (len == 0) return str;
    
    // 从末尾删除空格、制表符、换行符 - 后面的也不要
    char *end = str + len - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        *end = '\0';
        end--;
    }
    return str;
}

//用来解读用户输入的命令，变成电脑可以听懂的语言
// 功能：将用户输入的字符串解析成 Pipeline 结构，识别管道、重定向、后台运行等符号


// return 成功返回 0，失败返回 -1
int parse_command(char *line, Pipeline *pipeline)
{
    //恢复出场设置，初始化
    pipeline->cmd_count = 0;
    pipeline->background = 0;  // 初始化后台标志
    pipeline->cmds[0].argc = 0;//一个|管道，+1
    pipeline->cmds[0].input_file = NULL;
    pipeline->cmds[0].output_file = NULL;
    pipeline->cmds[0].append_mode = 0;//并非追加模式
    
    char *current_token = line;  // 当前解析位置 - 从这里开始读
    int current_cmd_idx = 0;     // 当前是第几个管道命令 - 管道符|的序号
    int arg_idx = 0;             // 当前命令的参数下标 - 第几个参数了
    
    // 逐字符扫描输入字符串 - 一个字符一个字符检查
    while (*current_token) 
    {
        // First，对管道符 | 下手 ，表示结束一个命令，开始下一个命令，把上一个命令的输出作为下一个命令的输入
        // 例如：ls | grep .txt 中的 |
        if (*current_token == '|') 
        {
            // 结束当前命令的参数列表 - 收尾
            pipeline->cmds[current_cmd_idx].args[arg_idx] = NULL;//把命令填上结尾
            pipeline->cmds[current_cmd_idx].argc = arg_idx;//记录命令长度，然后结束
            
            // 对下一个命令下手  -->继续初始化
            current_cmd_idx++;//注意注意注意！！！这里只有|会影响这玩意，只有这里要记得加，其他不用加
            if (current_cmd_idx >= MAX_PIPELINE) 
            {
                fprintf(stderr, "Too many commands in pipeline\n");
                return -1;
            }
            
            // 初始化下一个命令的结构
            pipeline->cmds[current_cmd_idx].argc = 0;
            pipeline->cmds[current_cmd_idx].input_file = NULL;
            pipeline->cmds[current_cmd_idx].output_file = NULL;
            pipeline->cmds[current_cmd_idx].append_mode = 0;
            arg_idx = 0;
            current_token++;
            continue;
        }
        
        // Second ，对&下手，表示后台运行
        // 支持 "sleep 10&" 和 "sleep 10 &" 两种写法
        // significant :& 只能出现在命令末尾，不允许 "sleep 10 & ls" 这种写法
        if (*current_token == '&') 
        {
            // 检查 & 后面是否还有非空白字符（除了行尾）
            char *check = current_token + 1;
            while (*check == ' ' || *check == '\t') check++;
            if (*check != '\0' && *check != '|') 
            {
                fprintf(stderr, "syntax error: & must be at end of command\n");
                pipeline->cmd_count = current_cmd_idx + 1;
                pipeline->cmds[current_cmd_idx].argc = arg_idx;
                free_pipeline(pipeline);
                return -1;
            }
            //background 现在属于 pipeline，而不是单个 command
            pipeline->background = 1;
            current_token++;
            continue;
        }
        
        //Third ，对 < 符号，表示输入重定向 
        if (*current_token == '<') 
        {
            current_token++;  // 跳过 < 
            while (*current_token == ' ')
            { 
                current_token++;  // 跳过空格 
            }
            char *start = current_token;  // 你标记了一处地点（doge ---> 文件名开始位置 
            // 一直读取到下一个分隔符 (排除法判断算了，反正就这几个符号)
            while (*current_token && *current_token != ' ' && *current_token != '|' && *current_token != '>' && *current_token != '<') 
            {
                current_token++;
            }
            
            char saved = *current_token;  // 保存终止字符（依旧标记地点）
            *current_token = '\0';         // 截断字符串 
                        
            // 复制文件名字符串 - 防背刺：检查是否失败
            pipeline->cmds[current_cmd_idx].input_file = strdup(start);
            if (!pipeline->cmds[current_cmd_idx].input_file) 
            {
                perror("strdup");
                // 失败时需要先设置 cmd_count，再释放已分配的内存
                pipeline->cmd_count = current_cmd_idx + 1;
                pipeline->cmds[current_cmd_idx].argc = arg_idx;
                free_pipeline(pipeline);
                return -1;
            }
            
            if (saved) current_token++;  // 如果不是'\0'的话，继续处理下一个字符 
            continue;
        }
        
        // Fourth，对 > 下手，输出重定向 
        if (*current_token == '>') 
        {
            current_token++;  // 跳过 > 
            int append = 0;   // 不追加，默认是覆盖模式 
            
            // 检查是否是 >>（追加模式） 
            if (*current_token == '>') //已经条到下一个了，可以直接看是不是>
            {
                append = 1;
                current_token++;
            }
            
            while (*current_token == ' ') current_token++;  // 跳过空格 
            
            char *start = current_token;  // 记录文件名开始位置 
            // 一直读取到下一个分隔符 
            while (*current_token && *current_token != ' ' && *current_token != '|' && *current_token != '>' && *current_token != '<') 
            {
                current_token++;
            }
            
            char saved = *current_token;  // 保存终止字符 
            *current_token = '\0';         // 截断字符串 
            
            // 复制文件名字符串并设置追加模式 - 防背刺：检查是否失败
            pipeline->cmds[current_cmd_idx].output_file = strdup(start);
            if (!pipeline->cmds[current_cmd_idx].output_file) 
            {
                perror("strdup");
                // 失败时需要先设置 cmd_count，再释放已分配的内存
                pipeline->cmd_count = current_cmd_idx + 1;
                pipeline->cmds[current_cmd_idx].argc = arg_idx;
                free_pipeline(pipeline);
                return -1;
            }
            pipeline->cmds[current_cmd_idx].append_mode = append;
            
            if (saved) current_token++;  // 继续处理下一个字符 
            continue;
        }
        
        //Fifth ，空格或\t（指标符） 
        if (*current_token == ' ' || *current_token == '\t') 
        {
            current_token++;
            continue;
        }
        
        // sixth，普通字符（命令或参数） 
        char *start = current_token;  // 依旧标记一处地点-->开始位置
        // 一直读取到下一个分隔符 
        while (*current_token && *current_token != ' ' && *current_token != '\t' && *current_token != '|' && *current_token != '>' && *current_token != '<' && *current_token != '&') //第一个条件是防止其为‘\0’
        {
            current_token++;
        }
        
        char saved = *current_token;  // 保存终止字符
        *current_token = '\0';         // 截断字符串 
        
        // 将单词添加到参数数组（注意防止数组越界） 
        if (arg_idx < MAX_ARGS - 1) //给\0 留位置
        {
            char *tmp = strdup(start);
            if (!tmp) {
                perror("strdup");
                // 失败时需要先设置 cmd_count，再释放已分配的内存
                pipeline->cmd_count = current_cmd_idx + 1;
                pipeline->cmds[current_cmd_idx].argc = arg_idx;
                free_pipeline(pipeline);
                return -1;
            }
            pipeline->cmds[current_cmd_idx].args[arg_idx++] = tmp;
        } else {
            fprintf(stderr, "too many arguments\n");
            // 失败时需要先设置 cmd_count，再释放已分配的内存
            pipeline->cmd_count = current_cmd_idx + 1;
            pipeline->cmds[current_cmd_idx].argc = arg_idx;
            free_pipeline(pipeline);
            return -1;
        }
        
        if (saved) current_token++;  // 继续处理下一个字符 
    }
    
    // 结束最后一个命令的参数列表 
    pipeline->cmds[current_cmd_idx].args[arg_idx] = NULL;
    pipeline->cmds[current_cmd_idx].argc = arg_idx;
    pipeline->cmd_count = current_cmd_idx + 1;
    
    // 【重要】检查空管道命令，如 "| ls" 或 "ls |"
    for (int i = 0; i < pipeline->cmd_count; i++) 
    {
        if (pipeline->cmds[i].argc == 0) 
        {
            fprintf(stderr, "syntax error: empty command in pipeline\n");
            free_pipeline(pipeline);
            return -1;
        }
    }
    
    return 0;
}



void free_command(Command *cmd)
{
    // 释放所有参数字符串 
    for (int i = 0; i < cmd->argc; i++) 
    {
        free(cmd->args[i]);
        cmd->args[i] = NULL;  // 防止野指针
    }
    cmd->argc = 0;
    
    // 释放输入文件名 
    if (cmd->input_file) 
    {
        free(cmd->input_file);
        cmd->input_file = NULL;
    }
    // 释放输出文件名 
    if (cmd->output_file) 
    {
        free(cmd->output_file);
        cmd->output_file = NULL;
    }
}//全都用过strdup，所以这里用free,不然艺术就是派大星（BOOM

void free_pipeline(Pipeline *pipeline)
{
    // 遍历所有命令并释放 
    for (int i = 0; i < pipeline->cmd_count; i++) 
    {
        free_command(&pipeline->cmds[i]);
    }
    pipeline->cmd_count = 0;  // 重置，防止重复释放
}

// 执行内建命令 (cd、exit 等)
// 
// return 是内建命令返回对应值，不是内建命令返回 -1
int execute_builtin(Command *cmd)
{
    // 处理 cd 命令：切换当前工作目录 
    if (strcmp(cmd->args[0], "cd") == 0)   //康康是否真的是cd命令
    {
        // 使用局部数组存储目标路径，避免指针直接赋值的问题 
        char target[MAX_PATH_LEN];
        
        // 如果没有参数，默认回到 $HOME
        if (cmd->argc < 2) 
        {
            char *home = getenv("HOME");
            if (!home) 
            {
                fprintf(stderr, "cd: HOME not set\n");
                return 1;
            }
            strncpy(target, home, MAX_PATH_LEN - 1);
            target[MAX_PATH_LEN - 1] = '\0';
        } 
        else 
        {
            // 【重要】支持 cd ~ 和 cd ~/xxx
            if (cmd->args[1][0] == '~') 
            {
                char *home = getenv("HOME");
                if (!home) 
                {
                    fprintf(stderr, "cd: HOME not set\n");
                    return 1;
                }
                // ~ 后面可能还有路径，如 ~/Documents
                snprintf(target, MAX_PATH_LEN, "%s%s", home, cmd->args[1] + 1);
            } 
            else 
            {
                strncpy(target, cmd->args[1], MAX_PATH_LEN - 1);
                target[MAX_PATH_LEN - 1] = '\0';  // 确保字符串正确结束
            }
        }
        
        // 处理 cd - ：返回上一个目录 
        if (strcmp(target, "-") == 0) 
        {
            if (last_dir[0] == '\0') 
            {
                fprintf(stderr, "cd: no previous directory\n");
                return 1;
            }
            printf("%s\n", last_dir);
            // 复制字符串内容，而不是直接赋值指针
            strncpy(target, last_dir, MAX_PATH_LEN - 1);
            target[MAX_PATH_LEN - 1] = '\0';
        }
        
        // 获取当前目录保存，以便后续 cd - 使用 
        char old_dir[MAX_PATH_LEN];
        if (getcwd(old_dir, sizeof(old_dir)) == NULL) 
        {
            perror("getcwd");
            return 1;
        }
        
        // 切换到目标目录（支持中文路径，因为 chdir 使用系统编码）  
        if (chdir(target) != 0) 
        {
            perror("cd");
            return 1;
        }
        
        // 更新上次目录记录，使用安全的字符串复制 
        strncpy(last_dir, old_dir, MAX_PATH_LEN - 1);  
        last_dir[MAX_PATH_LEN - 1] = '\0'; 
        return 0; 
    }
    
    // exit :跑路
    if (strcmp(cmd->args[0], "exit") == 0) 
    {
        // 注意：不在这里释放内存，由主循环统一释放
        // 避免双重释放
        return -999;  // 特殊返回值，通知主循环退出 
    }
    
    // 不是内建命令 
    return -1;
}

// 执行单个命令 (包含重定向处理)
//  cmd 要执行的 Command 结构指针
// stdin_fd 标准输入的文件描述符
//stdout_fd 标准输出的文件描述符
// return 执行失败返回 1，成功不返回 (直接 execvp)
int execute_command(Command *cmd, int stdin_fd, int stdout_fd)
{
    // 如果提供了自定义的 stdin_fd，则重定向标准输入
    if (stdin_fd != STDIN_FILENO) 
    {
        if (dup2(stdin_fd, STDIN_FILENO) < 0) 
        {
            perror("dup2 stdin");
            _exit(1);
        }
        close(stdin_fd);
    }
    
    // 如果提供了自定义的 stdout_fd，则重定向标准输出
    if (stdout_fd != STDOUT_FILENO) 
    {
        if (dup2(stdout_fd, STDOUT_FILENO) < 0) 
        {
            perror("dup2 stdout");
            _exit(1);
        }
        close(stdout_fd);
    }
    
    // 处理输入重定向：从指定文件读取
    if (cmd->input_file) 
    {
        int fd = open(cmd->input_file, O_RDONLY);
        if (fd < 0) 
        {
            perror(cmd->input_file);
            _exit(1);
        }
        if (dup2(fd, STDIN_FILENO) < 0) 
        {
            perror("dup2");
            _exit(1);
        }
        close(fd);
    }
    
    // 处理输出重定向：写入到指定文件
    if (cmd->output_file) 
    {
        int flags = O_WRONLY | O_CREAT | (cmd->append_mode ? O_APPEND : O_TRUNC);
        int fd = open(cmd->output_file, flags, 0644);
        if (fd < 0) 
        {
            perror(cmd->output_file);
            _exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0) 
        {
            perror("dup2");
            _exit(1);
        }
        close(fd);
    }
    
    // 执行外部命令
    execvp(cmd->args[0], cmd->args);
    
    // 注意！！！execvp 失败时，根据 errno 返回不同退出码
    // 127 = command not found (ENOENT)
    // 126 = permission denied 或其他错误
    perror(cmd->args[0]);
    if (errno == ENOENT) 
    {
        _exit(127);  // Unix 规范：command not found
    }
    _exit(126);  // permission denied 或其他执行错误
    
    return 127;  // 永远不会执行
}

// 执行管道中的所有命令 - 核心引擎
// pipeline 包含所有命令的 Pipeline 结构指针
// return 执行状态码
int execute_pipeline(Pipeline *pipeline)
{
    // 如果没有命令，直接返回 - 没活干，下班
    if (pipeline->cmd_count == 0) return 0;
    
    // 情况 1: 只有一个命令（不需要管道） - 单打独斗
    if (pipeline->cmd_count == 1) 
    {
        Command *cmd = &pipeline->cmds[0];
        
        // 空命令，跳过 - 啥也没有就跳过
        if (cmd->argc == 0) return 0;
        
        // 尝试执行内建命令 - cd、exit 这些
        int builtin_ret = execute_builtin(cmd);
        if (builtin_ret == -999) 
        {
            return -999;  // exit 命令，需要退出 - 特殊暗号
        }
        if (builtin_ret != -1) return builtin_ret;  // 内建命令已执行 - 不是外人
        
        // 不是内建命令，创建子进程执行外部命令 - ls、ps 这些
        pid_t pid = fork();
        if (pid < 0) 
        {
            perror("fork");  // 防背刺：创建子进程失败
            //注意！！！不在这里 free_pipeline，由调用者统一释放，避免 double free
            return 1;
        }
        
        if (pid == 0) 
        {
            // 子进程：恢复信号的默认处理方式 
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            // execute_command 内部会调用 _exit(127)，不会返回
            execute_command(cmd, STDIN_FILENO, STDOUT_FILENO);
            // 理论上不会到这里
            _exit(127);
        }
        
        // 父进程 
        if (!pipeline->background) 
        {
            // 前台运行：等待子进程结束 
            int status;
            //注意！！！使用特定 PID 等待，避免被 SIGCHLD handler 抢走
            // 并处理 EINTR（被信号中断）
            while (waitpid(pid, &status, 0) < 0) 
            {
                if (errno != EINTR) 
                {
                    perror("waitpid");
                    return 1;
                }
            }
            return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
        } else 
        {
            // 后台运行：打印进程号并立即返回 
            printf("[%d] %d\n", pipeline->cmd_count, pid);
            return 0;
        }
    }
    
    // 情况 2: 多个命令（需要管道） 
    
    // 创建 n-1 个管道（n 是命令数量） 
    int pipes[MAX_PIPELINE - 1][2];
    for (int i = 0; i < pipeline->cmd_count - 1; i++) {
        if (pipe(pipes[i]) < 0) 
        {
            perror("pipe");
            // 关闭已创建的管道
            for (int j = 0; j < i; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            //注意！！！不在这里 free_pipeline，由调用者统一释放，避免 double free
            return 1;
        }
    }
    
    // 存储所有子进程的 PID，初始化为 0 避免垃圾值
    pid_t pids[MAX_PIPELINE] = {0};
    
    // 为每个命令创建一个子进程 
    for (int i = 0; i < pipeline->cmd_count; i++) {
        Command *cmd = &pipeline->cmds[i];
        
        if (cmd->argc == 0) continue;
        
        pid_t pid = fork();
        if (pid < 0) 
        {
            perror("fork");
            // 关闭所有管道
            for (int j = 0; j < pipeline->cmd_count - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            //注意！！！不在这里 free_pipeline，由调用者统一释放，避免 double free
            return 1;
        }
        
        if (pid == 0) 
        {
            // 子进程：恢复信号默认处理 
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            
            //注意！！！正确顺序：先 dup2 需要的管道，再关闭所有管道
            // 如果不是第一个命令，从上游管道读取数据 
            if (i > 0) 
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            
            // 如果不是最后一个命令，向下游管道写入数据 
            if (i < pipeline->cmd_count - 1) 
            {
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            
            //注意！！！dup2 完成后，关闭所有管道的 FD
            // 避免管道 EOF 不触发，导致 like `yes | head` 挂住
            for (int j = 0; j < pipeline->cmd_count - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            
            //注意！！！重定向优先级：文件重定向 > 管道
            // execute_command 内部会再次处理 < > 重定向
            // 所以 "cmd1 | cmd2 > file" 最终 cmd2 输出到 file，符合 bash 行为
            execute_command(cmd, STDIN_FILENO, STDOUT_FILENO);
            // 理论上不会到这里
            _exit(127);
        }
        
        // 父进程记录子进程 PID 
        pids[i] = pid;
    }
    
    // 关闭所有管道的文件描述符（父进程不需要） 
    for (int i = 0; i < pipeline->cmd_count - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    
    // 检查是否是后台运行 
    int is_background = pipeline->background;
    
    if (!is_background) 
    {
        // 前台运行：等待所有子进程结束 
        for (int i = 0; i < pipeline->cmd_count; i++) {
            if (pids[i] > 0) 
            {
                int status;
                //注意！！！处理 EINTR（被信号中断）
                while (waitpid(pids[i], &status, 0) < 0) 
                {
                    if (errno != EINTR) break;
                }
            }
        }
    } else 
    {
        // 后台运行：打印所有子进程的 PID 
        printf("[%d]", pipeline->cmd_count);
        for (int i = 0; i < pipeline->cmd_count; i++) {
            if (pids[i] > 0) 
            {
                printf(" %d", pids[i]);
            }
        }
        printf("\n");
    }
    
    return 0;
}

// Shell 主循环
// 功能：不断读取用户输入、解析命令、执行命令，直到用户退出
void run_shell(void)
{
    char line[MAX_CMD_LEN];
    
    // 无限循环，持续接收用户命令 
    while (1) {
        // 步骤 1: 显示提示符 
        // 在读取输入前恢复信号默认处理，允许 Ctrl+C 中断输入
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        print_prompt();
        
        // 步骤 2: 读取一行输入 
        if (fgets(line, sizeof(line), stdin) == NULL) 
        {
            if (feof(stdin)) 
            {
                // 遇到 EOF（如 Ctrl+D），正常退出 
                printf("exit\n");
                break;
            }
            // 读取错误 
            perror("fgets");
            break;
        }
        
        // 重新忽略信号，准备执行命令
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        
        // 步骤 3: 去除首尾空白字符 
        char *trimmed = trim(line);
        if (strlen(trimmed) == 0) continue;  // 空行跳过 
        
        // 步骤 4: 解析命令 
        Pipeline pipeline;
        memset(&pipeline, 0, sizeof(pipeline));  // 初始化避免垃圾值
        if (parse_command(trimmed, &pipeline) < 0) 
        {
            continue;  // 解析失败，继续下一轮 
        }
        
        // 步骤 5: 执行命令 
        int ret = execute_pipeline(&pipeline);
        
        // 步骤 6: 释放内存 
        free_pipeline(&pipeline);
        
        // 步骤 7: 检查是否需要退出（exit 命令） 
        if (ret == -999) 
        {
            break;
        }
    }
}

// 主函数
// argc 参数个数
// argv 参数数组
int main(int argc, char *argv[])
{
    printf("this is Michael-Super-Shell \n");
    // 步骤 1: 初始化 Shell（信号处理、保存初始目录） 
    init_shell();
    
    // 步骤 2: 检查是否有脚本文件参数 
    if (argc > 1) 
    {
        // 有参数：以批处理模式执行脚本文件 
        FILE *script = fopen(argv[1], "r");
        if (!script) 
        {
            perror(argv[1]);
            return 1;
        }
        
        char line[MAX_CMD_LEN];
        // 逐行读取脚本文件 
        while (fgets(line, sizeof(line), script)) 
        {
            char *trimmed = trim(line);
            // 跳过空行和注释（#开头） 
            if (strlen(trimmed) == 0 || trimmed[0] == '#') continue;
            
            Pipeline pipeline;
            memset(&pipeline, 0, sizeof(pipeline));  // 初始化避免垃圾值
            if (parse_command(trimmed, &pipeline) < 0) 
            {
                continue;
            }
            
            int ret = execute_pipeline(&pipeline);
            free_pipeline(&pipeline);
            
            // 【重要】检查脚本中的 exit 命令
            if (ret == -999) 
            {
                fclose(script);
                return 0;
            }
        }
        
        fclose(script);
        return 0;
    }
    
    // 无参数：进入交互式 Shell 模式 
    run_shell();
    printf("\n感谢使用 Michael-Super-Shell\n");
    return 0;
}

