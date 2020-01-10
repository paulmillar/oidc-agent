#include "oidc-add.h"

#include "account/account.h"
#include "add_handler.h"
#ifndef __APPLE__
#include "privileges/add_privileges.h"
#endif
#include "utils/commonFeatures.h"
#include "utils/disableTracing.h"
#include "utils/file_io/fileUtils.h"
#include "utils/logger.h"

int main(int argc, char** argv) {
  platform_disable_tracing();
  logger_open("oidc-add");
  logger_setloglevel(NOTICE);
  struct arguments arguments;

  initArguments(&arguments);

  argp_parse(&argp, argc, argv, 0, 0, &arguments);
  if (arguments.debug) {
    logger_setloglevel(DEBUG);
  }
#ifndef __APPLE__
  if (arguments.seccomp) {
    initOidcAddPrivileges(&arguments);
  }
#endif

  if (arguments.listConfigured) {
    common_handleListConfiguredAccountConfigs();
    return EXIT_SUCCESS;
  }
  if (arguments.listLoaded) {
    add_handleListLoadedAccounts();
    return EXIT_SUCCESS;
  }
  if (arguments.removeAll) {
    add_handleRemoveAll();
    return EXIT_SUCCESS;
  }
  common_assertAgent();
  if (arguments.lock || arguments.unlock) {
    add_handleLock(arguments.lock);
    return EXIT_SUCCESS;
  }
  checkOidcDirExists();

  char* account = arguments.args[0];
  if (!accountConfigExists(account)) {
    oidc_errno = OIDC_ENOACCOUNT;
    oidc_perror();
    exit(EXIT_FAILURE);
  }
  if (arguments.print) {
    add_handlePrint(account, &arguments);
    return EXIT_SUCCESS;
  }

  if (arguments.remove) {
    add_handleRemove(account);
  } else {
    add_handleAdd(account, &arguments);
  }

  return EXIT_SUCCESS;
}
