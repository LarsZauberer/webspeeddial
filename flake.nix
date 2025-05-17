{
  description = "A speed dial system for websites";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: let
  	pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in {

    packages.x86_64-linux.default = pkgs.rustPlatform.buildRustPackage {
      pname = "webspeeddial";
      version = "1.0";
      cargoLock.lockFile = ./Cargo.lock;
      src = pkgs.lib.cleanSource ./.;
      nativeBuildInputs = [pkgs.makeWrapper];

      postFixup = ''
      	wrapProgram $out/bin/webspeeddial --prefix PATH : "${pkgs.lib.makeBinPath [pkgs.fzf pkgs.xdg-utils]}"
      '';
    };

  };
}
