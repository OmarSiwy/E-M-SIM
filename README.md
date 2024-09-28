# E-M-SIM

Simulations for Electric and Magnetic Fields for 2D Schematics

## To Build/Development:

**Windows**:

```PowerShell
# Install Chocolately
if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
    Write-Host "Installing Chocolatey..."
    Set-ExecutionPolicy Bypass -Scope Process -Force;
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072;
    Invoke-Expression ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'));
} else {
    Write-Host "Chocolatey is already installed."
}

# Install Docker
if (-not (Get-Command docker -ErrorAction SilentlyContinue)) {
    Write-Host "Installing Docker Desktop via Chocolatey..."
    choco install docker-desktop -y
} else {
    Write-Host "Docker Desktop is already installed."
}

# Install X11
if (-not (Get-Command Xming -ErrorAction SilentlyContinue)) {
    Write-Host "Installing Xming via Chocolatey..."
    choco install xming -y
} else {
    Write-Host "Xming is already installed."
}

# RUN:
xhost +local:docker && \
docker compose up --build
```

**Macos**:

```Bash
# Install brew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
# Install Docker
brew install --cask docker
# Install XMing
brew install --cask XQuartz

# RUN:
xhost +local:docker && \
docker compose up --build
```

**Linux**:

```Bash
# Install X11
depends on system
# Install Docker
depends on system

# RUN:
xhost +local:docker && \
docker compose up --build
```
