## Task 3: Dynamically Configured Logger Module

### Overview

This module implements a configurable logger with four logging levels:

- **LOG\_ERROR**
- **LOG\_WARNING**
- **LOG\_INFO**
- **LOG\_DEBUG**

The log level is controlled **dynamically at runtime** using a real-time signal. A separate application (`set_log_level`) sends signals to adjust the logging level.

### Usage

Example command to change the log level:

```sh
./logProcess.elf <wrong_file_name>
```

```sh
./chaneLevelProcess.elf error <processs_ID>
```

### Features

- Supports runtime log level changes.
- Uses signals for communication.
- Provides four logging levels for different verbosity levels.

