# System-project

下载后

修改两处

`./FTPclient/src/FTPcfg.h` 内的 ![image-20221006164814662](https://typora-1308069715.cos.ap-nanjing.myqcloud.com/img/image-20221006164814662.png)

和

`./http-server/src/cfg.h` 内的 ![image-20221006164911919](https://typora-1308069715.cos.ap-nanjing.myqcloud.com/img/image-20221006164911919.png)

两处路径为模型分配系统工作目录，需要保持一致。

修改后，拷贝`FTPclient` `http-server`两个文件夹到 TX2 上，或将文件夹挂载上去。

拷贝 `System`文件夹到上面设定的工作目录下。

接着分别对`FTPclient` `http-server`两个文件夹进行以下操作

```shell
mkdir build
cd build
cmake ..
make
```

编译完成后，在 build/bin 下会生成可执行文件。
