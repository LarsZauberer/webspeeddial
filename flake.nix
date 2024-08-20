{
  description = "A simple speed dialing system for websites";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {inherit system;};
        bi = with pkgs; [
          # Rust
          cargo
          rustc
          rustfmt

          # Make Rust work
          pkg-config
          stdenv.cc.libc
          clang
        ];

        nbi = with pkgs; [
          fzf
        ];

        # clang config
        clang_path = "${pkgs.llvmPackages.libclang.lib}/lib";

        # Package
        web-speeddial = pkgs.rustPlatform.buildRustPackage {
          name = "web_speeddial";
          src = ./.;
          cargoLock.lockFile = ./Cargo.lock;
          buildInputs = bi;
          nativeBuildInputs = nbi;
          LIBCLANG_PATH = clang_path;
        };
      in {
        packages.default = web-speeddial;

        devShell = pkgs.mkShell {
          buildInputs = bi;
          nativeBuildInputs = nbi;
          LIBCLANG_PATH = clang_path;
        };
      }
    );
}
