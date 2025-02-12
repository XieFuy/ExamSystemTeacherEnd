#include "dpihelper.h"

DpiHelper::DpiHelper()
{

}

DpiHelper::~DpiHelper()
{
    //进行设置回原来的dpi
    this->SetScalingPercentage(this->localScaling);
    qDebug()<<"dpiHelper 释放！";
}

//targetDpi=baseDpi× （缩放比例 /100）
bool DpiHelper::isRunningAsAdmin() {
    BOOL isAdmin = FALSE;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup)) {
        if (!CheckTokenMembership(NULL, AdministratorsGroup, &isAdmin)) {
            isAdmin = FALSE;
        }
        FreeSid(AdministratorsGroup);
    }
    return isAdmin;
}

bool DpiHelper::requestAdminRights() {
    wchar_t szPath[MAX_PATH];
    if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath))) {
        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.lpVerb = L"runas"; // 请求提升权限
        sei.lpFile = szPath;
        sei.hwnd = NULL;
        sei.nShow = SW_NORMAL;

        if (!ShellExecuteEx(&sei)) {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_CANCELLED) {
                QMessageBox::critical(nullptr, "错误", "管理员权限被拒绝，程序将退出。");
            }
            return false;
        }
        return true;
    }
    return false;
}

// 获取当前显示缩放比例
int DpiHelper::GetCurrentScalingPercentage() {
    HDC hdc = GetDC(NULL);
    int dpi = GetDeviceCaps(hdc, LOGPIXELSX);
    ReleaseDC(NULL, hdc);

    // 计算缩放比例
    int scalingPercentage = static_cast<int>((static_cast<float>(dpi) / 96.0f) * 100);
    return scalingPercentage;
}

// 设置显示缩放比例
bool DpiHelper::SetScalingPercentage(int scalingPercentage) {
    HKEY hKey;
    LONG result;

    // 打开注册表键
    result = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Control Panel\\Desktop"), 0, KEY_WRITE, &hKey);
    if (result != ERROR_SUCCESS) {
        qDebug()<< "Failed to open registry key.";
        return false;
    }

    // 计算目标 DPI 值
    int targetDpi = (96 * scalingPercentage) / 100;

    // 设置 LogPixels 值
    DWORD logPixels = static_cast<DWORD>(targetDpi);
    result = RegSetValueEx(hKey, TEXT("LogPixels"), 0, REG_DWORD, reinterpret_cast<BYTE*>(&logPixels), sizeof(logPixels));
    if (result != ERROR_SUCCESS) {
        qDebug()<< "Failed to set LogPixels value." ;
        RegCloseKey(hKey);
        return false;
    }

    // 设置 Win8DpiScaling 值
    DWORD win8DpiScaling = 1;
    result = RegSetValueEx(hKey, TEXT("Win8DpiScaling"), 0, REG_DWORD, reinterpret_cast<BYTE*>(&win8DpiScaling), sizeof(win8DpiScaling));
    if (result != ERROR_SUCCESS) {
        qDebug()<< "Failed to set Win8DpiScaling value." ;
        RegCloseKey(hKey);
        return false;
    }

    // 设置 DPIscalingVer 值
    DWORD dpiScalingVer = 0x00001018;
    result = RegSetValueEx(hKey, TEXT("DPIscalingVer"), 0, REG_DWORD, reinterpret_cast<BYTE*>(&dpiScalingVer), sizeof(dpiScalingVer));
    if (result != ERROR_SUCCESS) {
        qDebug()<< "Failed to set DPIscalingVer value." ;
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);

    // 通知系统设置已更改
    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)TEXT("Control Panel\\Desktop"), SMTO_NORMAL, 1000, NULL);

    return true;
}
