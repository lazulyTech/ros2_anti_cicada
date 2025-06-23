# ros2_anti_cicada
金森研チャレンジ2025製作物「セミ爆弾被害防止のためのセミ除去ロボットの開発」のROS 2ワークスペース

セミファイナルがとても嫌いなので、除去するというか、とりあえず自分の方に飛んでこないように突っつき回すロボットを作りました。  
MobileNetではセミを検出できない(モデルの作り方がわからないのと、セミの模型も用意したくなかった)ので、代わりに車(ミニカー)を検出します。

# 動かし方
1. コントローラを接続
2. 1つ目のターミナルで `ros2 launch depthai_examples mobile_publisher.launch.py` を実行
3. 2つ目のターミナルで `ros2 launch base_driver base_driver.launch.py` を実行

# とても参考にした本・サイト
- [するが電機工業「JLCPCBにお願いする全方向移動ロボット」](https://techbookfest.org/product/dsdu0kPgGBSn4W91ffCPZU?productVariantID=ra7mSJ780khw5G4Z1RmmtE)
- [きょうのかんぱぱ「TurtleBot2 kobukiがやってきた #7（ROS2 物体追尾編）」](https://kanpapa.com/2024/05/turtlebot2-kobuki-7-ros2-oak-d-lite.html)
