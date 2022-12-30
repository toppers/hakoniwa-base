# はじめに
本リポジトリでは、以下の環境を統合したシミュレーション環境を目指しています。

* https://github.com/toppers/hakoniwa-single_robot
* https://github.com/toppers/hakoniwa-ros2sim
* https://github.com/toppers/hakoniwa-ecu-multiplay
* https://github.com/toppers/hakoniwa-iot
* https://github.com/toppers/hakoniwa-ros-multiplay


アーキテクチャのイメージは下図の通りです(本図はマイコン制御向けのアーキテクチャ)。

![スクリーンショット 2022-12-24 21 43 52](https://user-images.githubusercontent.com/164193/210108299-482f0bee-2405-43c3-8730-9de4e4ab57d1.png)

# シミュレーション環境の構成

シミュレーション環境の構成として、以下の２つの環境が必要となります。

* [A] 制御対象ソフトウェアの開発環境
* [B] 制御対象ソフトウェアおよびハード・ロボットのシミュレーション実行環境

本リポジトリでは、[A]と[B]それぞれの環境をdockerコンテナとして提供します。

また、これらの環境は、利用するロボットの種類や数、制御で利用するプラットフォーム(RTOS, ROS等)によって、異なる環境を必要とします。

本リポジトリでは、そういった物をパラメータ化し、用途に応じた dockerコンテナを自動生成することを目指します。

現時点で検討中のパラメータは、こちらです。

* https://github.com/toppers/hakoniwa-develop/blob/main/params/ev3rt-one-instance.json

今後、ブラッシュアップしながら、成長させていく予定です。

# 環境

本シミュレーション環境に必要な環境は以下の通りです。

* OS
  * Windows10/11 の WSL2
  * Ubuntu 20.0.4, 22.0.4
  * Intel系のMac OS
* Docker
* Unity

# 進捗状況

`2022/12/31` 時点では、EV3RT での HackEV ロボット制御のシミュレーション環境のみ対応しています。

# インストール手順

```
git clone --recursive https://github.com/toppers/hakoniwa-develop.git
```

## 用途に応じたシミュレーション環境のパラメータ設定

`2022/12/31` 時点では、未対応です。

用途に応じたパラメータを json 形式で設定する予定です。

## Dockerファイルの生成

`2022/12/31` 時点では、未対応です。

設定したパラメータファイルから、開発環境と実行環境のDockerfileを自動生成する予定です。

## 開発環境のインストール

まず、開発環境用のdockerイメージを作成します。

```
cd hakoniwa-develop
bash docker/create-image.bash dev
```

docker コンテナを起動し、インストールコマンドを実行します(将来的にはここも自動化予定)。

```
bash docker/run.bash dev
bash install.bash
```

## 実行環境

次に、実行環境のdockerイメージを作成します。

```
cd hakoniwa-develop
bash docker/create-image.bash runtime
```

docker コンテナを起動し、インストールコマンドを実行します(将来的にはここも自動化予定)。

```
bash docker/run.bash dev
bash install.bash
```

# 開発環境のフォルダ構成とビルド方法

開発対象とする制御アプリケーションは、`workspace/dev/src` 直下に開発アプリのディレクトリを作成し、ファイル配置する形になります。

```
workspace/dev
└── src
    ├── [開発アプリディレクトリ]
    :     :
    ├── build.bash
    └── install.bash
```

開発環境のdockerコンテナを起動すると、`workspace/dev/src` がカレントディレクトリとなります。

アプリケーションのビルド方法は、開発環境のコンテナ内で、以下のコマンドを実行するだけです。

```
bash build.bash [開発アプリディレクトリ]
```

生成された実行バイナリは、ローカルホスト上のファイルとして生成されます。
EV3RTの場合は、[開発アプリディレクトリ]配下に、`asp` ファイルが作成されます。


# 技術背景

TODO
