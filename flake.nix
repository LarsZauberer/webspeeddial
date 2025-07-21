{
  description = "A speed dial system for websites";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = inputs: let
    pkgs = inputs.nixpkgs.legacyPackages.x86_64-linux;
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

    nixosModules = {
      default = {
        config,
        lib,
        pkgs,
        ...
      }: let
        cfg = config.programs.webspeeddial;
        webspeeddial-config = {
          runner = cfg.settings.runner;
          arguments = cfg.settings.arguments;
          bookmarks = cfg.settings.bookmarks;
        };
        yaml = pkgs.formats.yaml {};

        webspeeddial-wrapped = pkgs.symlinkJoin {
          name = "webspeeddial-wrapped";
          paths = [
            inputs.self.packages.x86_64-linux.default
          ];
          nativeBuildInputs = [pkgs.makeWrapper];
          postBuild = ''
            mkdir -p $out/config/webspeeddial
            cp "${yaml.generate "config.yml" webspeeddial-config}" "$out/config/webspeeddial/config.yml"
            wrapProgram $out/bin/webspeeddial --set XDG_CONFIG_HOME $out/config
          '';
        };
      in {
        options.programs.webspeeddial = {
          enable = lib.mkEnableOption "webspeeddial";
          settings = {
            runner = lib.mkOption {
              description = "Runner for the webspeeddial";
              type = lib.types.str;
              default = "${pkgs.fzf}/bin/fzf";
            };
            arguments = lib.mkOption {
              description = "The arguments passed to the runner for webspeeddial";
              type = lib.types.listOf (lib.types.str);
              default = [];
            };
            bookmarks = lib.mkOption {
              description = "webspeeddial booksmarks";
              type = lib.types.listOf (lib.types.attrs);
              default = [
                {
                  name = "Webspeeddial";
                  link = "https://github.com/LarsZauberer/webspeeddial";
                }
              ];
            };
          };
        };
        config = lib.mkIf cfg.enable {
          environment.systemPackages = [
            webspeeddial-wrapped
          ];
        };
      };
    };
  };
}
