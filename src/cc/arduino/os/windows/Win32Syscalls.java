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

package cc.arduino.os.windows;

import java.io.File;
import java.nio.file.Paths;

public class Win32Syscalls {

  static {
    System.loadLibrary("win32syscalls");
  }

  /**
   * Try to detect DPI settings for the system.
   * 
   * @return The current DPI settings.
   */
  public static native int detectSystemDPI();

  private static native String nativeGetLocalAppDataFolder();

  private static native String nativeGetRoamingAppDataFolder();

  private static native String nativeGetDocumentsFolder();

  /**
   * Retrieve the LocalAppData folder.
   * 
   * @return A File object for LocalAppData folder.
   */
  public static File getLocalAppDataFolder() {
    return new File(nativeGetLocalAppDataFolder());
  }

  /**
   * Retrieve the AppData folder.
   * 
   * @return A File object for AppData folder.
   */
  public static File getRoamingAppDataFolder() {
    return new File(nativeGetRoamingAppDataFolder());
  }

  /**
   * Retrieve the Documents folder.
   * 
   * @return A File object for Documents folder.
   */
  public static File getDocumentsFolder() {
    return new File(nativeGetDocumentsFolder());
  }

  /**
   * Retrieve the LocalCache folder. This is valid only for Windows Store apps.
   * 
   * @param appId
   *          The Windows Store app ID.
   * @return A File object for LocalCache folder.
   */
  public static File getLocalCacheFolder(String appId) {
    String localAppData = nativeGetLocalAppDataFolder();
    return Paths.get(localAppData, "Packages", appId, "LocalCache").toFile();
  }
}
