# FileTransfer
A tool that uses a relay server to upload and download files from remote clients.

# Motivation

My requirement was a tool with **minimal communication setup complexity**:

1. Run a **single Server**.
2. Let clients **A** and **B** connect to it.
3. **Done**—just start transferring files.

If transferring **directly from A to B**, I’d often need additional configuration (which, in practice, is rarely feasible due to on-site constraints). Debugging such setups is tedious, time-consuming, and sometimes outright impossible in restricted customer environments.

To address this, the tool includes a **console-only client** and a **Server** with **zero dependencies** (no third-party runtime required). It runs instantly—**no configuration needed** except specifying the Server’s IP.

# Introduce

The program is primarily divided into three parts:

- **GUI Client** (with a graphical interface), binary name is `FileTransferGUI`.
- **Console-only Client** (command-line version), binary name is `FileTransferConsole`.
- **Relay Server** (intermediary service), binary name is `FileTransferRelay`.

Let's assume you're using a gui-client named **`A`**. You can access files on a remote machine via **`FileTransferGUI`** (the target device can run either `FileTransferGUI` or `FileTransferConsole`, as long as both connect to the same **`FileTransferRelay`** server).

Notably, **`FileTransferConsole`** does not rely on the **Qt framework**. Its limitations include:

- Acting only as a server for **`A`** (not a true standalone server, but rather a server-like functionality).

However, it has a key advantage:

- **Broader compatibility**—it can run on more environments, such as lower version system **Windows XP** (or even older systems, though we don't officially support them—if you can compile it, you're free to try) or console only environments.

# Build

* C++20 Standard.

- Basic components (gui-client-side) for Qt5 and above.

# Feature

**Features the GUI Client Should Support:**

1. **Direct Download/Upload** – Transfer selected files/directories to/from the target device’s specified directory.
2. **Custom Path per File** – Allow assigning different download/upload paths for individual files.
3. **Individual Progress Bars** – Display separate progress indicators for each file transfer.
4. **UI-Independent Core** – Keep communication logic completely separate from UI libraries.
5. **UTF-8 Encoding** – Strictly enforce UTF-8 across all components.
6. **Interface-Based Interaction** – Core communicates with UI/console via defined interfaces.
7. **Legacy Console Handling** – If the console (e.g., Windows XP) cannot print UTF-8, suppress output and log to file (UTF-8).
8. **Dedicated Task UI** – A separate window to list all transfer tasks with checkable operations.
9. **Progress Monitoring** – Dual progress bars during transfers (overall + current file), with cancel/abort options.
10. **Task History** – Save task records (unique names, default = timestamp).
11. **Transfer Flags** – Configurable options (e.g., overwrite, skip existing).
12. **Pre-Transfer Validation** – Verify target file existence before starting.
13. **C++20 Compliance** – Enforce compiler standardization.
14. **Client Aliasing** – Assign random (but persistent) dictionary-based names to identify `IP:PORT`.
15. **Basic Encryption** – Implement secure transfers via TinyAES.
16. **Resume Support** – Allow interrupted downloads to be resumed.
17. **SHA256 Verification** – Optionally validate file integrity post-transfer.
18. **Filtering** – Enable file/folder filtering during selection.
19. **TBD** *(To be expanded based on further requirements)*
