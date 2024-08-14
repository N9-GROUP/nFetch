#include "get_sys.h"
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>

SystemInfo get_system_info() {
  SystemInfo sys_info;

  // Получаем информацию о системе
  struct utsname uname_info;
  if (uname(&uname_info) == -1) {
    strcpy(sys_info.kernel, "Unknown");
    strcpy(sys_info.os, "Unknown");
    strcpy(sys_info.device_name, "Unknown");
  } else {
    // Получаем версию ядра
    strcpy(sys_info.kernel, uname_info.release);

    // Получаем название системы
    strcpy(sys_info.os, uname_info.sysname);

    // Получаем имя устройства
    strcpy(sys_info.device_name, uname_info.nodename);
  }

  // Получаем оболочку
  char *shell = getenv("SHELL");
  if (shell == NULL) {
    strcpy(sys_info.shell, "Unknown");
  } else {
    char *shell_name = strrchr(shell, '/');
    if (shell_name == NULL) {
      strcpy(sys_info.shell, shell);
    } else {
      strcpy(sys_info.shell, shell_name + 1);
    }
  }

  // Получаем имя пользователя
  struct passwd *pw = getpwuid(getuid());
  if (pw == NULL) {
    strcpy(sys_info.username, "Unknown");
  } else {
    strcpy(sys_info.username, pw->pw_name);
  }

  return sys_info;
}