# Prebuilt hbm for AOSP build, built with cargo-ndk

This is a repo containing prebuilts of olv's [hbm](https://gitlab.freedesktop.org/olv/hbm) project. Currently include:
- hbm-minigbm static library for x86/x86_64, API level 34 (Android 14)
- hbm_minigbm.h header created with cbindgen

I created this repo to support hbm on older Android, and also I don't know how to write Android.bp with Rust on Android 14+ yet :p

The repo will focus mostly on `hbm-minigbm`. However, if `hbm` have interesting development in `hbm-gralloc`, I'll include it in too.

## How to build

1. Get Rust with Rustup

It's recommend to uninstall Rust packages that is provided by your linux distro and use `rustup` to install instead

```
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

2. Install cbindgen

cbindgen can be installed with

```
cargo install cbindgen
```

2. Follow cargo-ndk instructions to setup the build environment

`cargo-ndk` has an instruction on the project's README, you can follow it and get the build environment ready

https://github.com/bbqsrc/cargo-ndk?tab=readme-ov-file#installing

Also remember to download NDK as the `Usage` part pointed out, set `ANDROID_NDK_HOME` to the extracted place if it can't scan your NDK location.

4. Build

The following commands will build hbm-minigbm for x86/x86_64 with API 34 and generate hbm_minigbm.h

```
cargo ndk -t x86 -t x86_64 -p 34 build --package hbm-minigbm --release
cbindgen -o hbm_minigbm.h hbm-minigbm
```

Grab the prebuilts on `target/` and the header `hbm_minigbm.h` once done !
