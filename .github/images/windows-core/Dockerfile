# escape=`

ARG FROM_IMAGE=mcr.microsoft.com/windows:ltsc2019
FROM ${FROM_IMAGE}

LABEL maintainer="sebastian.termen@gmail.com"

# Reset the shell.
SHELL ["cmd", "/S", "/C"]

ENV STRAWBERRY_PERL_VERSION=5.32.1.1
ENV PYTHON_VERSION=3.9.7

RUN powershell -Command Write-Host "Windows Docker initialized."

# Set up environment to collect install errors.
COPY Install.cmd C:\TEMP\
ADD https://aka.ms/vscollect.exe C:\TEMP\collect.exe

# Download channel for fixed install.
ARG CHANNEL_URL=https://aka.ms/vs/17/release/channel
ADD ${CHANNEL_URL} C:\TEMP\VisualStudio.chman

# Download and install Build Tools for Visual Studio 2022.
ADD https://aka.ms/vs/17/release/vs_buildtools.exe C:\TEMP\vs_buildtools.exe
RUN C:\TEMP\Install.cmd C:\TEMP\vs_buildtools.exe --quiet --wait --norestart --nocache `
    --channelUri C:\TEMP\VisualStudio.chman `
    --installChannelUri C:\TEMP\VisualStudio.chman `
    --add Microsoft.Component.MSBuild `
    --add Microsoft.VisualStudio.Component.VC.CoreIde `
    --add Microsoft.VisualStudio.Component.VC.DiagnosticTools `
    --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
    --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended`
    --add Microsoft.VisualStudio.Component.VC.143 `
    --add Microsoft.VisualStudio.Component.Windows10SDK `
    --add Microsoft.VisualStudio.Component.Windows11SDK.22621 `
    --installPath C:\BuildTools

# Download and install PowerShell Core
RUN powershell Invoke-WebRequest -Uri https://github.com/PowerShell/PowerShell/releases/download/v7.2.1/PowerShell-7.2.1-win-x64.msi -OutFile C:\powershell.msi ; `
    Start-Process -Wait -FilePath msiexec.exe -ArgumentList '/i', 'C:\powershell.msi', '/quiet', '/norestart' ; `
    Remove-Item C:\powershell.msi -Force

# Set environment variables for PowerShell Core
ENV PATH="${PATH};C:\Windows\System32\WindowsPowerShell\v1.0"

# Download and install 7-Zip
RUN powershell Invoke-WebRequest -Uri https://www.7-zip.org/a/7z2301-x64.exe -OutFile C:\7zip.exe ; `
    Start-Process -Wait -FilePath C:\7zip.exe -ArgumentList '/S' ; `
    Remove-Item -Path C:\7zip.exe -Force

# Set environment variables for 7-zip
ENV PATH="${PATH};C:\Program Files\7-Zip"

# Download and install Git
RUN powershell -Command Invoke-WebRequest -Uri https://github.com/git-for-windows/git/releases/download/v2.42.0.windows.2/Git-2.42.0.2-64-bit.exe -OutFile C:\git-installer.exe ; `
    Start-Process -Wait -FilePath C:\git-installer.exe -ArgumentList '/VERYSILENT', '/NORESTART' ; `
    Remove-Item C:\git-installer.exe -Force

# Set environment variables for Git
ENV PATH="${PATH};C:\Program Files\Git\cmd"

# Download and install CMake
RUN powershell -Command Invoke-WebRequest -Uri https://github.com/Kitware/CMake/releases/download/v3.27.4/cmake-3.27.4-windows-x86_64.msi -OutFile C:\cmake-installer.msi ; `
    Start-Process -Wait -FilePath msiexec.exe -ArgumentList '/i', 'C:\cmake-installer.msi', '/quiet', '/norestart' ; `
    Remove-Item C:\cmake-installer.msi -Force

# Set environment variables for CMake
ENV PATH="${PATH};C:\Program Files\CMake\bin"

# Download and install Strawberry Perl
RUN powershell -Command Invoke-WebRequest -Uri https://strawberryperl.com/download/5.32.1.1/strawberry-perl-5.32.1.1-64bit.msi -OutFile C:\strawberry-perl-installer.msi ; `
    Start-Process -Wait -FilePath msiexec.exe -ArgumentList '/i', 'C:\strawberry-perl-installer.msi', '/quiet', '/norestart' ; `
    Remove-Item C:\strawberry-perl-installer.msi -Force

# Set environment variables for Strawberry Perl
ENV PATH="${PATH};C:\Strawberry\perl\bin;C:\Strawberry\perl\site\bin;C:\Strawberry\c\bin"

# Download and install Python
RUN powershell -Command Invoke-WebRequest -Uri https://www.python.org/ftp/python/3.11.5/python-3.11.5-amd64.exe -OutFile C:\python-installer.exe ; `
    Start-Process -Wait -FilePath C:\python-installer.exe -ArgumentList '/quiet', 'TargetDir=C:\Python', 'Include_launcher=0' ; `
    Remove-Item C:\python-installer.exe -Force

# Set environment variables for Python
ENV PATH="${PATH};C:\Python;C:\Python\Scripts"

# Set environment variables for MSVC v143
ENV PATH="${PATH};C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild"
ENV PATH="${PATH};C:\BuildTools\VC\Tools\MSVC\14.37.32822\bin\Hostx64\x64"

# RUN dir "C:\BuildTools\VC\Auxiliary\Build"
# RUN dir "C:\Program Files (x86)\Microsoft Visual Studio"
# RUN dir "C:\BuildTools\VC\Tools\MSVC\14.37.32822\bin\Hostx64\x64"
# RUN dir /s /b "C:\BuildTools\cl.exe"
# RUN dir "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild"

# Clone vcpkg repository using Git
RUN git clone https://github.com/microsoft/vcpkg.git C:\vcpkg

# Bootstrap vcpkg (build vcpkg itself)
# WORKDIR C:\vcpkg
RUN C:\vcpkg\bootstrap-vcpkg.bat

# Set environment variables for vcpkg
ENV VCPKG_DEFAULT_TRIPLET=x64-windows
ENV PATH="${PATH};C:\vcpkg"

# Get all the dependencies for the project
RUN vcpkg install fmt --triplet=x64-windows
RUN vcpkg install spdlog --triplet=x64-windows
RUN vcpkg install stb --triplet=x64-windows
RUN vcpkg install pkgconf --triplet=x64-windows
RUN vcpkg install raylib --triplet=x64-windows
RUN vcpkg install gtest --triplet=x64-windows
RUN vcpkg install boost --triplet=x64-windows
RUN vcpkg install boost-python[python3] --triplet=x64-windows
RUN vcpkg install gtkmm --triplet=x64-windows
RUN vcpkg install opengl --triplet=x64-windows
RUN vcpkg install vcpkg-pkgconfig-get-modules --triplet=x64-windows

# Integrate vcpkg
RUN vcpkg integrate install
RUN vcpkg integrate powershell
RUN cd C:\vcpkg\installed\x64-windows\tools\boost-build && powershell .\bootstrap.bat & cd C:\

# Check dependencies
RUN vcpkg list

# Use developer command prompt and start PowerShell if no other command specified.
# ENTRYPOINT C:\BuildTools\Common7\Tools\VsDevCmd.bat &&
# CMD ["powershell.exe", "-NoLogo", "-ExecutionPolicy", "Bypass"]