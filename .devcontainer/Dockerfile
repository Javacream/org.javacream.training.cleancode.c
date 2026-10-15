FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

# Compiler, Debugger und statische Analyse für die C90-Übungen.
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
       build-essential gcc gdb make valgrind cppcheck python3 python3-venv \
    && rm -rf /var/lib/apt/lists/*

# Lizard isoliert installieren (Ubuntu 24.04 schützt System-Python via PEP 668).
RUN python3 -m venv /opt/metrics-venv \
    && /opt/metrics-venv/bin/pip install --no-cache-dir lizard
ENV PATH="/opt/metrics-venv/bin:${PATH}"
