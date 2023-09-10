FROM mcr.microsoft.com/windows/servercore:ltsc2022

LABEL maintainer="sebastian.termen@gmail.com"

RUN powershell -Command Write-Host "Windows Docker initialized."

ENV STRAWBERRY_PERL_VERSION=5.32.1.1
ENV PYTHON_VERSION=3.9.7

# Download and install PowerShell Core
RUN powershell Invoke-WebRequest -Uri https://github.com/PowerShell/PowerShell/releases/download/v7.2.1/PowerShell-7.2.1-win-x64.msi -OutFile C:\powershell.msi ; \
    Start-Process -Wait -FilePath msiexec.exe -ArgumentList '/i', 'C:\powershell.msi', '/quiet', '/norestart' ; \
    Remove-Item C:\powershell.msi -Force

# Download and install 7-Zip
RUN powershell Invoke-WebRequest -Uri https://www.7-zip.org/a/7z2301-x64.exe -OutFile C:\7zip.exe ; \
    Start-Process -Wait -FilePath C:\7zip.exe -ArgumentList '/S' ; \
    Remove-Item -Path C:\7zip.exe -Force

# Download vcpkg archive
RUN powershell Invoke-WebRequest -Uri https://github.com/microsoft/vcpkg/archive/refs/tags/2023.08.09.tar.gz -OutFile C:\vcpkg.tar.gz

# Extract vcpkg archive using 7-Zip and rename the extracted folder
# run dir "C:\Program Files\7-Zip"
RUN "C:\Progra~1\7-Zip\7z.exe" x C:\vcpkg.tar.gz -oC:
RUN Rename-Item -Path C:\vcpkg-2023.08.09 -NewName vcpkg
RUN Remove-Item -Path C:\vcpkg.tar.gz -Force

# Remove the temporary archive file
# RUN Remove-Item -Path C:\vcpkg.tar.gz -Force

# # Download and install vcpkg
# RUN powershell -Command Invoke-WebRequest -Uri https://github.com/microsoft/vcpkg/archive/refs/tags/2023.08.09.tar.gz -OutFile C:\vcpkg.tar.gz ; \
#     Expand-Archive -Path C:\vcpkg.tar.gz -DestinationPath C:\ ; \
#     Rename-Item -Path C:\vcpkg-2022.08 -NewName vcpkg ; \
#     Remove-Item C:\vcpkg.tar.gz -Force

# # Download and install Git
# RUN powershell -Command Invoke-WebRequest -Uri https://github.com/git-for-windows/git/releases/download/v2.42.0.windows.2/Git-2.42.0.2-64-bit.exe -OutFile C:\git-installer.exe ; \
#     Start-Process -Wait -FilePath C:\git-installer.exe -ArgumentList '/VERYSILENT', '/NORESTART' ; \
#     Remove-Item C:\git-installer.exe -Force

# # Download and install CMake
# RUN powershell -Command Invoke-WebRequest -Uri https://github.com/Kitware/CMake/releases/download/v3.27.4/cmake-3.27.4-windows-x86_64.msi -OutFile C:\cmake-installer.msi ; \
#     Start-Process -Wait -FilePath msiexec.exe -ArgumentList '/i', 'C:\cmake-installer.msi', '/quiet', '/norestart' ; \
#     Remove-Item C:\cmake-installer.msi -Force

# # Download and install Strawberry Perl
# RUN powershell -Command Invoke-WebRequest -Uri https://strawberryperl.com/download/5.32.1.1/strawberry-perl-5.32.1.1-64bit.msi -OutFile C:\strawberry-perl-installer.msi ; \
#     Start-Process -Wait -FilePath msiexec.exe -ArgumentList '/i', 'C:\strawberry-perl-installer.msi', '/quiet', '/norestart' ; \
#     Remove-Item C:\strawberry-perl-installer.msi -Force

# # Download and install Python
# RUN powershell -Command Invoke-WebRequest -Uri https://www.python.org/ftp/python/3.11.5/python-3.11.5-amd64.exe -OutFile C:\python-installer.exe ; \
#     Start-Process -Wait -FilePath C:\python-installer.exe -ArgumentList '/quiet', 'TargetDir=C:\Python', 'Include_launcher=0' ; \
#     Remove-Item C:\python-installer.exe -Force

# # Download and install Visual C++ Build Tools (MSVC v143)
# # Replace the URL with the appropriate URL for the version you need
# RUN powershell -Command Invoke-WebRequest -Uri https://aka.ms/vs/16/release/vs_buildtools.exe -OutFile C:\vs_buildtools_installer.exe ; \
#     Start-Process -Wait -FilePath C:\vs_buildtools_installer.exe -ArgumentList '--norestart', '--add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Workload.MSBuildTools' ; \
#     Remove-Item C:\vs_buildtools_installer.exe -Force

# # Set environment variables for MSVC v143
# # ENV PATH="${PATH};C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64"
# ENV PATH="${PATH};C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.37.32822\bin\Hostx64\x64"

