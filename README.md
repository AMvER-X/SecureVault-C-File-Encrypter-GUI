# SecureVault-C++-File-Encrypter-GUI

SecureVault v1.0
A High-Performance Batch File Encryption Engine

SecureVault is a robust, multi-threaded C++ application built with the Qt 6 framework and libsodium, designed for secure data at rest. It provides a streamlined interface for batch processing sensitive files with a focus on cryptographic integrity and user experience.

🛠 Core Technical Features
Cryptographic Agnostic Logic: While currently utilizing AES-256-GCM via libsodium, the architecture is decoupled to allow for rapid integration of post-quantum or alternative symmetric algorithms.

Automatic State Detection: Unlike primitive encryptors, SecureVault uses File Signature Analysis (Magic Numbers) rather than unreliable file extensions to determine if a file is encrypted or plaintext.

Non-Blocking Multithreading: Utilizes a Worker-Object pattern with QThread. The UI remains responsive during heavy I/O operations, ensuring the application never "hangs" during large batch processes.

Smart Queue Management: Supports drag-and-drop file ingestion and real-time queue manipulation, allowing users to prioritize or remove assets before the cryptographic loop begins.

🔒 Security Architecture & Libsodium
I chose libsodium as the cryptographic backbone because it is a portable, cross-compilable, and highly "misuse-resistant" library.

Stress-Tested & Audited: Libsodium is the gold standard for modern applications, designed by security experts to prevent common side-channel attacks and padding oracle vulnerabilities found in older libraries.

Authenticated Encryption (AEAD): SecureVault doesn't just hide data; it ensures integrity. Using AEAD modes ensures that if an attacker modifies even a single bit of the encrypted file, the decryption process will fail rather than outputting "garbage" data.

Memory Safety: The implementation focuses on secure buffer handling and explicit memory clearing to prevent sensitive keys from leaking into swap space.

🚀 Professional Highlights (For Recruiters)
If you are reviewing this for a Cybersecurity or Software Engineering role, please note:

Memory Management: Implements RAII (Resource Acquisition Is Initialization) patterns to prevent memory leaks in the C++ backend.

Error Handling: Features a robust "Fail-Safe" I/O system. If a write operation fails (disk full, permission denied), the engine halts and protects the original source file from corruption.

Scalable Batching: The current v1.0 handles files sequentially to maintain I/O stability on standard hardware, with a planned upgrade to a thread-pool architecture for concurrent processing.

🗺 Roadmap
v1.1: Implementation of Argon2id for superior password-based key derivation (KDF).

v1.2: Parallel I/O processing using QtConcurrent for high-speed NVMe optimization.

v1.3: Integration of RSA/ECC for asymmetric key exchange.
