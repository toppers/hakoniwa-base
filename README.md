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

* https://github.com/toppers/hakoniwa-base/blob/main/params/ev3rt-one-instance.json

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
git clone --recursive https://github.com/toppers/hakoniwa-base.git
```

## 用途に応じたシミュレーション環境のパラメータ設定

`2022/12/31` 時点では、未対応です。

用途に応じたパラメータを json 形式で設定する予定です。

## Dockerファイルの生成

`2022/12/31` 時点では、未対応です。

設定したパラメータファイルから、開発環境と実行環境のDockerfileおよび環境変数群を自動生成する予定です。

## 開発環境のインストール

まず、開発環境用のdockerイメージを作成します。

```
cd hakoniwa-base
bash docker/create-image.bash dev
```

## 実行環境

次に、実行環境のdockerイメージを作成します。

```
cd hakoniwa-base
bash docker/create-image.bash runtime
```

## Unity環境のセットアップ

### インストール

まず、以下のリポジトリをクローンします。

```
git clone --recursive https://github.com/toppers/hakoniwa-ros2sim.git
```

次に、ブランチを`unity-asset`に切り替えます。

```
git checkout unity-asset
```

docker コンテナを起動します。

```
 bash docker/run.bash 
```

もろもろインストールします。

```
 bash hako-install.bash opt all
```

[こちらの手順](https://github.com/toppers/hakoniwa-ros2sim/blob/main/README_jp.md#unity-%E3%83%97%E3%83%AD%E3%82%B8%E3%82%A7%E3%82%AF%E3%83%88%E3%82%92%E9%96%8B%E3%81%8F)で、Unity プロジェクトを開いてください。

### ロボットの配置

箱庭コンフィギュレータを起動すると、下図のようにTB3が見えます。

![image](https://user-images.githubusercontent.com/164193/210113179-b29d8df1-a490-4217-b011-f36075aa4a42.png)


今回は、HackEVモデルを利用したいので、TB3は削除して、HackEVを配置します。

まず、TB3を以下の要領で削除します。

![image](https://user-images.githubusercontent.com/164193/210113222-e9b24d99-7898-43b5-aed0-36954413207d.png)

箱庭のロボットアセットを開き、HackEVモデルを選択します。

![image](https://user-images.githubusercontent.com/164193/210113272-cb46072a-c5ed-4ca2-aa91-a7460369b020.png)

ドラッグ＆ドロップで、「Robot」直下に配置しましょう。

![image](https://user-images.githubusercontent.com/164193/210113323-80dda1d3-340c-49cd-a3e9-79691e9c605d.png)

最後に、この情報をコンフィグファイルとして生成します。

![image](https://user-images.githubusercontent.com/164193/210113357-2a679abc-d87d-4126-8ba0-96341b93c7be.png)

生成完了したら、再度、もろもろインストールします。

```
 bash hako-install.bash opt all
```



# 開発環境のディレクトリ構成とビルド方法

開発対象とする制御アプリケーションは、`workspace/dev/src` 直下に開発アプリのディレクトリを作成し、ファイル配置する形になります。

```
workspace/dev
└── src
    ├── [開発アプリディレクトリ]
    :     :
    ├── build.bash
    └── install.bash
```

開発環境でのビルドは、dockerコンテナ上で行います。
アプリケーションのビルド方法は、以下のコマンドを実行するだけです。

```
bash docker/build.bash [開発アプリディレクトリ名]
```

生成された実行バイナリは、ローカルホスト上のファイルとして生成されます。

EV3RTの場合は、[開発アプリディレクトリ]配下に、`asp` ファイルが作成されます。

# シミュレーション実行手順

開発環境と同様に、実行環境もローカルホスト上に、シミュレーション実行に必要なファイル群を保存する構成です。

ディレクトリ構成は以下の通りです。


```
workspace/runtime/
├── asset_def.txt
├── asset_env.bash
├── hakoniwa-core-cpp-client
├── hakoniwa-master-rust
├── install.bash
├── params
│   ├── base_practice_1-1
│   │   ├── device_config.txt
│   │   ├── memory.txt
│   │   └── proxy_config.json
│   ├── block_signal-1
│   │   ├── device_config.txt
│   │   ├── memory.txt
│   │   └── proxy_config.json
│   └── train_slow_stop-1
│       ├── device_config.txt
│       ├── memory.txt
│       └── proxy_config.json
├── run
│   ├── base_practice_1-1
│   ├── block_signal-1
│   │   └── log.txt
│   └── train_slow_stop-1
│       └── log.txt
└── run.bash
```

シミュレーション実行対象となるアセットは `asset_def.txt` に記述します。

```
<開発アプリディレクトリ名>:<ID>
　：
```

例：

```
block_signal:1
train_slow_stop:1
```

ところで、複数のathrillを同時に起動すると、コンソールログが重複して大変なことになります。
そのような場合に備えて、Athrillのログを特定の場所に吐き出すコンフィグ設定が可能です。

```
<開発アプリディレクトリ名>:<ID>:<ログ出力ファイルパス>
　：
```

例：

```
block_signal:1:root/workspace/run/block_signal-1/debug.txt
train_slow_stop:1:root/workspace/run/train_slow_stop-1/debug.txt
```


## 実行環境の起動

docker コンテナを起動するだけです。

```
bash docker/run.bash runtime
```

成功すると、[Rust版箱庭マスタ](https://github.com/toppers/hakoniwa-master-rust)と[箱庭プロキシ](https://github.com/toppers/hakoniwa-core-cpp-client/blob/3070fed43c9534f1a6209798b24510750ad63783/src/proxy/src/hako_proxy.cpp)が起動します。


```
$ bash docker/run.bash runtime
INFO: ACTIVATING HAKO-MASTER
INFO: ACTIVATING ASSET-PROXY
OPEN RECIEVER UDP PORT=172.26.214.23:54001
OPEN SENDER UDP PORT=172.26.214.23:54002
delta_msec = 20
max_delay_msec = 100
INFO: shmget() key=255 size=12160 
Server Start: 172.26.214.23:50051
INFO: START block_signal-1
add_option:/root/athrill-target-v850e2m/athrill/bin/linux/athrill2
add_option:-c1
add_option:-t
add_option:-1
add_option:-d
add_option:/root/workspace/params/block_signal-1/device_config.txt
add_option:-m
add_option:/root/workspace/params/block_signal-1/memory.txt
add_option:/root/workspace/dev/block_signal/asp
INFO: PROXY start
target_channels: 0 target_channels: 1024
create_channel: id=2 size=1024
INFO: START train_slow_stop-1
INFO: SIMULATION READY!
add_option:/root/athrill-target-v850e2m/athrill/bin/linux/athrill2
add_option:-c1
add_option:-t
add_option:-1
add_option:-d
add_option:/root/workspace/params/train_slow_stop-1/device_config.txt
add_option:-m
add_option:/root/workspace/params/train_slow_stop-1/memory.txt
add_option:/root/workspace/dev/train_slow_stop/asp
INFO: PROXY start
target_channels: 0 target_channels: 1024
create_channel: id=0 size=1024
```


## Unityのシミュレーション実行

Unityエディタ上で、シーンを`Toppers_Course`に切り替えます。

![image](https://user-images.githubusercontent.com/164193/210114913-ef502c0b-3b17-4afb-a402-e9010451edab.png)

シミュレーション開始ボタンを押下します。

![image](https://user-images.githubusercontent.com/164193/210114921-68828af6-8a97-42fc-bfc8-b3af3b5a6ddb.png)

シミュレーション実行待ち状態になります。

![image](https://user-images.githubusercontent.com/164193/210114954-f864725a-13c5-47f7-9d9d-be1767ffec1b.png)

「開始」ボタンを押下すると、動き出します。

動作例：



https://user-images.githubusercontent.com/164193/210167332-f685d856-a19b-4471-944f-7f9f03bb1e47.mp4





# 技術背景

TODO
