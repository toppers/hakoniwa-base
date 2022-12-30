# hakoniwa-develop

本リポジトリでは、以下の環境を統合したシミュレーション環境を目指しています。

* https://github.com/toppers/hakoniwa-single_robot
* https://github.com/toppers/hakoniwa-ros2sim
* https://github.com/toppers/hakoniwa-ecu-multiplay
* https://github.com/toppers/hakoniwa-iot
* https://github.com/toppers/hakoniwa-ros-multiplay

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


