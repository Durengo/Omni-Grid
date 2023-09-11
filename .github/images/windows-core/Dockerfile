FROM mcr.microsoft.com/windows/servercore:ltsc2022

LABEL maintainer="sebastian.termen@gmail.com"

RUN powershell -Command Write-Host "Windows Docker initialized."

SHELL ["cmd", "/S", "/C"]

ENV STRAWBERRY_PERL_VERSION=5.32.1.1
ENV PYTHON_VERSION=3.9.7
ENV vs_installer_url=https://aka.ms/vs/16/release/channel
ENV vs_workload_id=Microsoft.VisualStudio.Workload.NativeDesktop

# # Download and install PowerShell Core
# RUN powershell Invoke-WebRequest -Uri https://github.com/PowerShell/PowerShell/releases/download/v7.2.1/PowerShell-7.2.1-win-x64.msi -OutFile C:\powershell.msi ; \
#     Start-Process -Wait -FilePath msiexec.exe -ArgumentList '/i', 'C:\powershell.msi', '/quiet', '/norestart' ; \
#     Remove-Item C:\powershell.msi -Force

# Set environment variables for PowerShell Core
ENV PATH="${PATH};C:\Windows\System32\WindowsPowerShell\v1.0"

# # Download and install 7-Zip
# RUN powershell Invoke-WebRequest -Uri https://www.7-zip.org/a/7z2301-x64.exe -OutFile C:\7zip.exe ; \
#     Start-Process -Wait -FilePath C:\7zip.exe -ArgumentList '/S' ; \
#     Remove-Item -Path C:\7zip.exe -Force

# # Set environment variables for 7-zip
# ENV PATH="${PATH};C:\Program Files\7-Zip"

# Download and install Git
RUN powershell -Command Invoke-WebRequest -Uri https://github.com/git-for-windows/git/releases/download/v2.42.0.windows.2/Git-2.42.0.2-64-bit.exe -OutFile C:\git-installer.exe ; \
    Start-Process -Wait -FilePath C:\git-installer.exe -ArgumentList '/VERYSILENT', '/NORESTART' ; \
    Remove-Item C:\git-installer.exe -Force

# Set environment variables for Git
ENV PATH="${PATH};C:\Program Files\Git\cmd"

# Clone vcpkg repository using Git
RUN git clone https://github.com/microsoft/vcpkg.git C:\vcpkg

# Bootstrap vcpkg (build vcpkg itself)
# WORKDIR C:\vcpkg
RUN C:\vcpkg\bootstrap-vcpkg.bat

# Set environment variables for vcpkg
ENV VCPKG_DEFAULT_TRIPLET=x64-windows-static
ENV PATH="${PATH};C:\vcpkg"

# # Download and install CMake
# RUN powershell -Command Invoke-WebRequest -Uri https://github.com/Kitware/CMake/releases/download/v3.27.4/cmake-3.27.4-windows-x86_64.msi -OutFile C:\cmake-installer.msi ; \
#     Start-Process -Wait -FilePath msiexec.exe -ArgumentList '/i', 'C:\cmake-installer.msi', '/quiet', '/norestart' ; \
#     Remove-Item C:\cmake-installer.msi -Force

# # Set environment variables for CMake
# ENV PATH="${PATH};C:\Program Files\CMake\bin"

# # Download and install Strawberry Perl
# RUN powershell -Command Invoke-WebRequest -Uri https://strawberryperl.com/download/5.32.1.1/strawberry-perl-5.32.1.1-64bit.msi -OutFile C:\strawberry-perl-installer.msi ; \
#     Start-Process -Wait -FilePath msiexec.exe -ArgumentList '/i', 'C:\strawberry-perl-installer.msi', '/quiet', '/norestart' ; \
#     Remove-Item C:\strawberry-perl-installer.msi -Force

# # Set environment variables for Strawberry Perl
# ENV PATH="${PATH};C:\Strawberry\perl\bin;C:\Strawberry\perl\site\bin;C:\Strawberry\c\bin"

# # Download and install Python
# RUN powershell -Command Invoke-WebRequest -Uri https://www.python.org/ftp/python/3.11.5/python-3.11.5-amd64.exe -OutFile C:\python-installer.exe ; \
#     Start-Process -Wait -FilePath C:\python-installer.exe -ArgumentList '/quiet', 'TargetDir=C:\Python', 'Include_launcher=0' ; \
#     Remove-Item C:\python-installer.exe -Force

# # Set environment variables for Python
# ENV PATH="${PATH};C:\Python;C:\Python\Scripts"

# Download and install Visual C++ Build Tools (MSVC v143)
# Replace the URL with the appropriate URL for the version you need
# RUN powershell -Command Invoke-WebRequest -Uri https://aka.ms/vs/16/release/vs_buildtools.exe -OutFile C:\vs_buildtools_installer.exe ; \
#     Start-Process -Wait -FilePath C:\vs_buildtools_installer.exe -ArgumentList '--norestart', '--add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Workload.MSBuildTools' ; \
#     Remove-Item C:\vs_buildtools_installer.exe -Force

# Download Visual Studio Build Tools installer
RUN powershell -Command Invoke-WebRequest -Uri https://aka.ms/vs/16/release/vs_buildtools.exe -OutFile C:\vs_buildtools.exe -UseBasicParsing

# Install Visual Studio Build Tools with the C++ workload
RUN C:\vs_buildtools.exe --installPath C:\vs_buildtools --quiet --add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64

# Clean up
RUN powershell Remove-Item -Path C:\vs_buildtools.exe -Force

# Set environment variables for MSVC v143
# ENV PATH="${PATH};C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64"
# ENV PATH="${PATH};C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.37.32822\bin\Hostx64\x64"

RUN dir "C:\Program Files (x86)\"

# Get all the dependencies for the project
RUN vcpkg install fmt --triplet=x64-windows-static
# RUN vcpkg install spdlog --triplet=x64-windows
# RUN vcpkg install stb --triplet=x64-windows
# RUN vcpkg install pkgconf --triplet=x64-windows
# RUN vcpkg install raylib --triplet=x64-windows
# RUN vcpkg install gtest --triplet=x64-windows
# RUN vcpkg install boost --triplet=x64-windows
# RUN vcpkg install boost-python[python3] --triplet=x64-windows
# RUN vcpkg install gtkmm --triplet=x64-windows
# RUN vcpkg install opengl --triplet=x64-windows
# RUN vcpkg install vcpkg-pkgconfig-get-modules --triplet=x64-windows

# # Integrate vcpkg
# RUN vcpkg integrate install
# RUN vcpkg integrate powershell
# RUN C:\vcpkg\installed\x64-windows\tools\boost-build\bootstrap.bat

# # Check dependencies
# RUN vcpkg list