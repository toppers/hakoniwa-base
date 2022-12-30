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

設定したパラメータファイルから、開発環境と実行環境のDockerfileおよび環境変数群を自動生成する予定です。

現状は、以下のファイルのパラメータを手動で設定してください。``

* docker/docker_runtime/env.bash
  * ETHER
    * 利用しているイーサーネット名(ifconfigコマンド確認できます)
  * CORE_IPADDR
    * 上記のIPアドレス

設定例は、以下の通りです。

https://github.com/toppers/hakoniwa-develop/blob/b2b0e4f6ba8ca3aea073a6c3f663782d47513229/docker/docker_runtime/env.bash#L9-L10

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


### コンフィグパラメータの変更

`hakoniwa-ros2sim/ros2/unity/tb3` 内に、様々な箱庭コンフィグファイルが json 形式で配置されています。
今回は、以下のファイルを更新する必要があります。（将来的には自動化予定）

* pdu_readers_config.json
* pdu_writers_config.json
* pdu_channel_connectors.json
* reader_connectors.json
* writer_connectors.json
* core_config.json

#### pdu_readers_config.json

`class_name` と `conv_class_name` を Ev3 からRaw に変更します。

![image](https://user-images.githubusercontent.com/164193/210114186-bbeb93cb-771d-4842-b8dc-2f03fabc38b5.png)

#### pdu_writers_config.json

`class_name` と `conv_class_name` を Ev3 からRaw に変更します。

![image](https://user-images.githubusercontent.com/164193/210114278-979fecba-92fb-4468-89d5-f076d8288cd4.png)

#### pdu_channel_connectors.json

`outside_asset_name` を Athrill から None に変更します。

![image](https://user-images.githubusercontent.com/164193/210114306-159257d8-81c4-4d96-9625-4ddccd1372c6.png)

#### reader_connectors.json

`method_name`を Udp から Rpc に変更します。

![image](https://user-images.githubusercontent.com/164193/210114339-845cb4fd-c0c0-4f9b-ae40-75ae859a1cfb.png)


#### writer_connectors.json

`method_name`を Udp から Rpc に変更します。

![image](https://user-images.githubusercontent.com/164193/210114360-47265958-2159-47be-919e-255a3d0685c4.png)

#### core_config.json

以下のパラメータを変更します。

* core_ipaddr
  * シミュレーション実行用のdockerコンテナのIPアドレス
* cpp_mode
  * asset_rpc
    * 箱庭マスタ機能と gRPC で連携するモードです。
    * 直接関数コールする場合は、`asset` とすれば行けますが、まだ非公開機能です。
* cpp_asset_name
  * UnityAssetRpc
    * 任意の名前でよいですが、20文字以内。
* asset_ipaddr
   * Unity配置PCのIPアドレス
* pdu_udp_portno_asset
   * 箱庭マスタ側から、PDUデータ受信するUDPポート番号
   * こだわりなければ、54003
* pdu_bin_offset_package_dir
  * PDUデータフォーマットファイル配置パス。`./offset`固定。
* udp_methods_path
  * 削除してください。
* rpc_methods_path
  * 箱庭マスタとgRPC通信するための各種パラメータ設定
  * `./rpc_methods.json`固定
 
![image](https://user-images.githubusercontent.com/164193/210114390-cc4e68c6-c4d8-4008-b89b-2c089dc78d04.png)


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

開発環境のdockerコンテナを起動すると、`workspace/dev/src` がカレントディレクトリとなります。

アプリケーションのビルド方法は、開発環境のコンテナ内で、以下のコマンドを実行するだけです。

```
bash build.bash [開発アプリディレクトリ]
```

生成された実行バイナリは、ローカルホスト上のファイルとして生成されます。

EV3RTの場合は、[開発アプリディレクトリ]配下に、`asp` ファイルが作成されます。

# シミュレーション実行手順

開発環境と同様に、実行環境もローカルホスト上に、シミュレーション実行に必要なファイル群を保存する構成です。

ディレクトリ構成は以下の通りです。

```
workspace/runtime
├── hakoniwa-core-cpp-client
├── hakoniwa-master-rust
├── install.bash
├── asset_env.bash
├── dev
├── params
│   ├── device_config.txt
│   ├── memory.txt
│   └── proxy_config.json
├── run-[アセット名]
└── run.bash
```

## 実行バイナリの配置

ホスト上で、開発環境で作成したバイナリファイルを`workspace/runtime/dev/`直下に配置してください。

例：

```
cp workspace/dev/src/[開発アプリディレクトリ]/asp workspace/runtime/dev/asp
```
## 実行環境の起動

docker コンテナを起動するだけです。

```
bash docker/run.bash runtime
```

成功すると、[Rust版箱庭マスタ](https://github.com/toppers/hakoniwa-master-rust)と[箱庭プロキシ](https://github.com/toppers/hakoniwa-core-cpp-client/blob/3070fed43c9534f1a6209798b24510750ad63783/src/proxy/src/hako_proxy.cpp)が起動します。


TODO 成功時のログを追記。


## Unityのシミュレーション実行

Unityエディタ上で、シーンを`Toppers_Course`に切り替えます。

![image](https://user-images.githubusercontent.com/164193/210114913-ef502c0b-3b17-4afb-a402-e9010451edab.png)

シミュレーション開始ボタンを押下します。

![image](https://user-images.githubusercontent.com/164193/210114921-68828af6-8a97-42fc-bfc8-b3af3b5a6ddb.png)

シミュレーション実行待ち状態になります。

![image](https://user-images.githubusercontent.com/164193/210114954-f864725a-13c5-47f7-9d9d-be1767ffec1b.png)

「開始」ボタンを押下すると、動き出します。

動作例：

https://user-images.githubusercontent.com/164193/210114879-5059d95a-b8d7-453f-bd1c-0c334e84410d.mp4




# 技術背景

TODO
