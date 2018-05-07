// Copyright 2016 The Chromium Embedded Framework Authors. Portions copyright
// 2016 The Chromium Authors. All rights reserved. Use of this source code is
// governed by a BSD-style license that can be found in the LICENSE file.

#ifndef CEF_LIBCEF_COMMON_CRASH_REPORTER_CLIENT_H_
#define CEF_LIBCEF_COMMON_CRASH_REPORTER_CLIENT_H_

#include <string>
#include <vector>

// Include this first to avoid compiler errors.
#include "base/compiler_specific.h"

#include "include/cef_version.h"

#include "base/macros.h"
#include "base/synchronization/lock.h"
#include "build/build_config.h"
#include "components/crash/content/app/crash_reporter_client.h"

// Global object that is instantiated in each process and configures crash
// reporting. On Windows this is created by the
// InitializeCrashReportingForProcess() method called from chrome_elf. On
// Linux and macOS this is created by crash_reporting::BasicStartupComplete().
class CefCrashReporterClient : public crash_reporter::CrashReporterClient {
 public:
  CefCrashReporterClient();
  ~CefCrashReporterClient() override;

  // Reads the crash config file and returns true on success. Failure to read
  // the crash config file will disable crash reporting. This method should be
  // called immediately after the CefCrashReporterClient instance is created.
  bool ReadCrashConfigFile();
  bool HasCrashConfigFile() const;

#if defined(OS_WIN)
  // Called from chrome_elf (chrome_elf/crash/crash_helper.cc) to instantiate
  // a process wide instance of CefCrashReporterClient and initialize crash
  // reporting for the process. The instance is leaked.
  // crash_reporting_win::InitializeCrashReportingForModule() will be called
  // later from crash_reporting::PreSandboxStartup() to read global state into
  // the module address space.
  static void InitializeCrashReportingForProcess();

  bool GetAlternativeCrashDumpLocation(base::string16* crash_dir) override;
  void GetProductNameAndVersion(const base::string16& exe_path,
                                base::string16* product_name,
                                base::string16* version,
                                base::string16* special_build,
                                base::string16* channel_name) override;
  bool GetCrashDumpLocation(base::string16* crash_dir) override;
  bool GetCrashMetricsLocation(base::string16* metrics_dir) override;
#elif defined(OS_POSIX)
  void GetProductNameAndVersion(const char** product_name,
                                const char** version) override;
  void GetProductNameAndVersion(const char** product_name,
                                const char** version,
                                const char** channel) override;
#if !defined(OS_MACOSX)
  base::FilePath GetReporterLogFilename() override;
  bool EnableBreakpadForProcess(const std::string& process_type) override;
#endif
  bool GetCrashDumpLocation(base::FilePath* crash_dir) override;
#endif  // defined(OS_POSIX)

  // All of these methods must return true to enable crash report upload.
  bool GetCollectStatsConsent() override;
  bool GetCollectStatsInSample() override;
#if defined(OS_WIN) || defined(OS_MACOSX)
  bool ReportingIsEnforcedByPolicy(bool* crashpad_enabled) override;
#endif

#if defined(OS_POSIX) && !defined(OS_MACOSX)
  bool IsRunningUnattended() override;
#endif

  std::string GetCrashServerURL() override;
  void GetCrashOptionalArguments(std::vector<std::string>* arguments) override;

#if defined(OS_WIN)
  base::string16 GetCrashExternalHandler(
      const base::string16& exe_dir) override;
  bool HasCrashExternalHandler() const;
#endif

#if defined(OS_MACOSX)
  bool EnableBrowserCrashForwarding() override;
#endif

#if defined(OS_POSIX) && !defined(OS_MACOSX)
  ParameterMap FilterParameters(const ParameterMap& parameters) override;
#endif

  // Set or clear a crash key value.
  bool SetCrashKeyValue(const base::StringPiece& key,
                        const base::StringPiece& value);

 private:
  bool has_crash_config_file_ = false;

  enum KeySize { SMALL_SIZE, MEDIUM_SIZE, LARGE_SIZE };

  // Map of crash key name to (KeySize, index).
  // Const access to |crash_keys_| is thread-safe after initialization.
  using KeyMap = std::map<std::string, std::pair<KeySize, size_t>>;
  KeyMap crash_keys_;

  // Modification of CrashKeyString values must be synchronized.
  base::Lock crash_key_lock_;

  std::string server_url_;
  bool rate_limit_ = true;
  int max_uploads_ = 5;
  int max_db_size_ = 20;
  int max_db_age_ = 5;

  std::string product_name_ = "cef";
  std::string product_version_ = CEF_VERSION;

#if defined(OS_WIN)
  std::string app_name_ = "CEF";
  std::string external_handler_;
#endif

#if defined(OS_MACOSX)
  bool enable_browser_crash_forwarding_ = false;
#endif

  DISALLOW_COPY_AND_ASSIGN(CefCrashReporterClient);
};

#endif  // CEF_LIBCEF_COMMON_CRASH_REPORTER_CLIENT_H_
