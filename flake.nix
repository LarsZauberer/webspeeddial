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
        ];

        nbi = with pkgs; [
          python3
        ];

        /*
           script = pkgs.stdenv.mkDerivation (finalAttrs: {
          pname = "webspeeddial";
          version = "0.1";

          outputs = ["out"];

          src = ./.;

          buildInputs = bi;
          nativeBuildInputs = nbi;

          installPhase = ''
            mkdir -p $out/bin
            cp -rv $src/main.py $out/bin/webspeeddial.py
          '';

          meta = {};
        });
        */
        script = pkgs.python3Packages.buildPythonApplication {
          pname = "webspeeddial";
          version = "0.1";

          nativeBuildInputs = nbi;

          src = ./.;
        };
      in {
        packages.default = script;

        devShell = pkgs.mkShell {
          buildInputs = bi;
          nativeBuildInputs = nbi;
        };
      }
    );
}
