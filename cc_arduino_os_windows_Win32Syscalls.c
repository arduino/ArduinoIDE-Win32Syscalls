/*
 * This file is part of Arduino.
 *
 * Copyright 2017 Arduino LLC (http://www.arduino.cc/)
 *
 * Arduino is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As a special exception, you may use this file as part of a free software
 * library without restriction.  Specifically, if other files instantiate
 * templates or use macros or inline functions from this file, or you compile
 * this file and link it with other files to produce an executable, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU General Public License.  This exception does not however
 * invalidate any other reasons why the executable file might be covered by
 * the GNU General Public License.
 */

#include "cc_arduino_os_windows_Win32Syscalls.h"

#include <windows.h>
#include <VersionHelpers.h>
#include <ShellScalingAPI.h>
#include <Shlobj.h>

JNIEXPORT jint JNICALL Java_cc_arduino_os_windows_Win32Syscalls_detectSystemDPI(JNIEnv *env, jclass cls) {
  if (IsWindows8Point1OrGreater()) {
	SetProcessDpiAwareness(DPI_AWARENESS_SYSTEM_AWARE);

    if (IsWindows10OrGreater()) {
      SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
      return GetDpiForSystem();
    }
  }

  return -1;
}

JNIEXPORT jstring JNICALL Java_cc_arduino_os_windows_Win32Syscalls_nativeGetLocalAppDataFolder(JNIEnv *env, jclass cls) {
  if (IsWindowsVistaOrGreater()) {
    wchar_t* localAppData = 0;
    SHGetKnownFolderPath(&FOLDERID_LocalAppData, 0, NULL, &localAppData);
    jstring res = (*env)->NewString(env, localAppData, wcslen(localAppData));
    CoTaskMemFree(localAppData);
    return res;
  }

  TCHAR localAppData[MAX_PATH];
  SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, localAppData);
  return (*env)->NewStringUTF(env, localAppData);
}

JNIEXPORT jstring JNICALL Java_cc_arduino_os_windows_Win32Syscalls_nativeGetRoamingAppDataFolder(JNIEnv *env, jclass cls) {
  if (IsWindowsVistaOrGreater()) {
    wchar_t* appData = 0;
    SHGetKnownFolderPath(&FOLDERID_RoamingAppData, 0, NULL, &appData);
    jstring res = (*env)->NewString(env, appData, wcslen(appData));
    CoTaskMemFree(appData);
    return res;
  }

  TCHAR appData[MAX_PATH];
  SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, appData);
  return (*env)->NewStringUTF(env, appData);
}

JNIEXPORT jstring JNICALL Java_cc_arduino_os_windows_Win32Syscalls_nativeGetDocumentsFolder(JNIEnv *env, jclass cls) {
  if (IsWindowsVistaOrGreater()) {
    wchar_t* docs = 0;
    SHGetKnownFolderPath(&FOLDERID_Documents, 0, NULL, &docs);
    jstring res = (*env)->NewString(env, docs, wcslen(docs));
    CoTaskMemFree(docs);
    return res;
  }

  TCHAR docs[MAX_PATH];
  SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, docs);
  return (*env)->NewStringUTF(env, docs);
}
