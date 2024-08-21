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

        python_script = pkgs.python3Packages.buildPythonApplication {
          pname = "webspeeddial";
          version = "1.0";

          nativeBuildInputs = nbi;

          src = ./.;

          installPhase = ''
            mkdir -p $out/bin
            cp ${./main.py} $out/bin/webspeeddial
            chmod +x $out/bin/webspeeddial
          '';
        };
      in {
        packages.default = python_script;
        apps.default = flake-utils.lib.mkApp {drv = self.packages.${system}.default;};

        devShell = pkgs.mkShell {
          buildInputs = bi;
          nativeBuildInputs = nbi;
        };
      }
    );
}
