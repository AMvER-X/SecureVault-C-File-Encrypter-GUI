# SecureVault-C++-File-Encrypter-GUI

# SecureVault v1.0
A High-Performance Batch File Encryption Engine

SecureVault is a robust, multi-threaded C++ application built with the Qt 6 framework and libsodium, designed for secure data at rest. It provides a streamlined interface for batch processing sensitive files with a focus on cryptographic integrity and system-level performance.

🛠 Core Technical Features
Cryptographic Agnostic Logic: Utilizing AES-256-GCM via libsodium, the architecture is decoupled to allow for future integration of post-quantum or alternative symmetric algorithms.

Automatic State Detection: SecureVault uses File Signature Analysis (Magic Numbers) rather than unreliable file extensions to determine if a file is encrypted or plaintext.

Non-Blocking Multithreading: Employs the Worker-Object pattern with QThread. Cryptographic operations are offloaded from the Main GUI thread to prevent interface freezing during high-density I/O.

Smart Queue Management: Supports drag-and-drop file ingestion and real-time queue manipulation, allowing users to prioritize or remove assets dynamically.

#🔒 Security Architecture & Cryptography
I chose libsodium as the cryptographic backbone because it is a portable, audited, and "misuse-resistant" library.

Password Hashing & Key Derivation (Argon2id)
SecureVault implements Argon2id, the state-of-the-art Key Derivation Function. Unlike traditional hashing, Argon2id is specifically designed to be:

GPU/ASIC Resistant: Configurable memory and iteration costs make brute-forcing passwords computationally expensive for attackers.

Side-Channel Resistant: Provides protection against time-based cache attacks.

Authenticated Keys: This ensures that the key used for AES-256-GCM is cryptographically strong, even if the user's password is relatively simple.

# Authenticated Encryption (AEAD)
SecureVault utilizes Authenticated Encryption with Associated Data (AEAD). This doesn't just provide confidentiality; it provides integrity. If an attacker modifies even a single bit of the encrypted ciphertext, the decryption process will detect the tampering and fail immediately, preventing "chosen-ciphertext" attacks.

Memory Safety
The implementation focuses on secure buffer handling. By using fixed-size buffers for I/O (64KB chunks), the application maintains a low memory footprint and prevents memory exhaustion when processing multi-gigabyte files.

# 🚀 Professional Highlights (For Recruiters)
If you are reviewing this for a Cybersecurity or Software Engineering role, please note:

I/O Integrity: Features a robust "Fail-Safe" I/O system. If a write operation fails (disk full, permission denied), the engine halts and protects the original source file from corruption.

Resource Management: Implements RAII (Resource Acquisition Is Initialization) patterns and smart pointers to ensure zero memory leaks in the C++ backend.

Chunked Processing: Demonstrates competence in system-level programming by streaming data through buffers rather than loading entire files into RAM.

🗺 Roadmap
v1.2: Parallel I/O processing using QtConcurrent for high-speed NVMe optimization.

v1.3: Integration of RSA/ECC for asymmetric key exchange and digital signatures.

v1.4: Secure memory-locking (mlock) to prevent sensitive data from being swapped to disk.
