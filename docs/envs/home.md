# Linux开发环境概述

!!! Warning "文档建设中……"
    当前的课程文档与代码仍在建设中，欢迎您通过GitHub提出建议与贡献。

## 开发环境的选择

本教程所选用的主要环境是ubuntu22.04长支持版本，如果有条件的话，笔者推荐在真机上进行。

!!! info "学习OpenCV时使用Linux的好处"

    1. 开源和社区支持：Linux是一个开源操作系统，拥有强大的开发者社区支持。这意味着你可以找到大量的资源、教程和开源项目，这些都对学习OpenCV非常有帮助。
    2. 软件兼容性：OpenCV是一个跨平台的计算机视觉和机器学习库，它在Linux上的兼容性非常好。Linux环境下，OpenCV的安装和配置相对简单，可以充分发挥其性能。
    3. 开发工具链：Linux提供了强大的开发工具链，如GCC、G++、CMake等，这些都是开发OpenCV项目时必不可少的工具。

而要想使用Linux环境，有以下选择。

=== "虚拟机安装"

    - 环境隔离：虚拟机可以提供独立的操作系统环境，这意味着你可以在不影响主机操作系统的情况下进行实验和配置。
    - 易于管理：通过虚拟机管理软件（如VirtualBox或VMware），你可以轻松地创建、克隆和删除Linux环境，不必担心损害主力系统。

=== "WSL2(Win11)"

    - 与Windows系统无缝集成：WSL2允许你在Windows环境下直接运行Linux命令，这对于同时需要Windows软件和Linux环境的用户来说非常方便。
    - 性能提升：WSL2相比于WSL1有显著的性能提升，特别是文件系统性能和网络性能，使得开发效率更高。

=== "真机安装Linux"

    - 最佳性能：在物理硬件上运行Linux可以获得最佳的性能，这对于需要大量计算资源的OpenCV项目来说尤其重要。
    - 系统定制性：物理安装的Linux系统通常提供更高的系统定制性，你可以根据需求优化系统配置，以适应特定的开发任务。

=== "docker"

    - 环境一致性：Docker容器提供了可移植的环境，这意味着你可以在任何支持Docker的操作系统上运行相同的环境，无论是在Windows、macOS还是Linux上。这对于确保代码在不同机器上的一致性运行非常有用。
    - 快速部署：通过Docker，你可以快速部署OpenCV环境，不需要手动安装各种依赖库和工具。只需下载相应的Docker镜像，运行容器，即可开始工作。
    - 隔离性：Docker容器之间是相互隔离的，这意味着你可以为不同的OpenCV项目或不同版本创建独立的容器，而不必担心它们之间会相互影响。

以上几种方式都是可行的，不过由于个人的基础有所不同，前置知识不同，到底应该选择哪种方式因人而异，不存在哪种好哪种坏的区别；因此关于到底应该选择哪种方式进行学习，笔者有以下建议：

首先将你的基础分为以下等级：

    1. 熟练操作Windows系统下的文件夹。
    2. 具备根据文档成功安装“学习版”软件而不求助淘宝的能力。（考虑到可能的读者的专业，包括`ARM MDK` 、`AD`、`SolidWorks`、`Vivado`、`MatLab`、`Jetbrain系列`以及学习版游戏等。）
    3. 有使用虚拟机软件的经验。
    4. 较熟练地使用shell（当然包括powershell）。
    5. 具备折腾Linux的经验（至少有真机装系统经验）。

如果你能够做到第五条，那么我会推荐你就使用已经安装的Linux安装或者在已经安装的Linux系统中使用Docker构建一个ubuntu容器进行学习；

如果你能够做到第四条，那么应该能够比较容易地上手WSL2这一Windows11出现的利器（Win10的WSL1体验并不算友好），当然你也可以选择使用Docker或真机安装；

如果你能够做到第二条，但是对于后面几条都不熟悉或者感到比较困难，那么或许虚拟机是更适合你的选择——不必感到任何沮丧，虚拟机并不比真机或WSL2弱上一筹，恰恰相反，如果在不熟悉Linux命令行的时候就使用WSL2这种没有图形界面的方式操作，可能会给你带来一些不必要的压力从而消磨学习的积极性。

!!! Note "环境只是手段"

    请不必为了开发环境而纠结，环境是为人服务的；在技术群聊或讨论帖里，会有这样一些人，他们贬低别人的工具链，推崇自己所使用的工具链，在虚拟机这方面，可能会出现痛斥虚拟机利用率低占用高等现象，并狂热要求你使用真机安装；请忽略他们，这是没有意义的，我们一般把这种人称为赛博邪教。在当前阶段适合你的才是最好的。

## 开发环境搭建准备

!!! question "到底要选哪个呢？"
    
    笔者在上一节给出了一些环境搭建的建议，但是这并不一定是完全适合你的，你可以考虑更多的己身需求，查阅更多相关资料，有根据地选择自己的开发环境吗？

当你选择好了自己准备使用的开发环境后，我将会提供相关的资料如下。但具体的使用方式将会在后面文档中介绍

### 使用虚拟机搭建开发环境

- 虚拟机软件：
    - [VMWare](https://www.vmware.com/)
    - [Virtualbox](https://www.virtualbox.org/)

- Ubuntu2204镜像：笔者提供的都是桌面版镜像，学习阶段和日常使用没有必要使用服务器版。
    - [Ubuntu（推荐）](https://mirrors.tuna.tsinghua.edu.cn/ubuntu-releases/jammy/ubuntu-22.04.4-desktop-amd64.iso)
    - [Kubuntu](https://mirrors.tuna.tsinghua.edu.cn/ubuntu-cdimage/kubuntu/releases/jammy/release/kubuntu-22.04.4-desktop-amd64.iso)
    - [Xubuntu](https://mirrors.tuna.tsinghua.edu.cn/ubuntu-cdimage/xubuntu/releases/jammy/release/xubuntu-22.04.4-desktop-amd64.iso)
    - [Lubuntu](https://mirrors.tuna.tsinghua.edu.cn/ubuntu-cdimage/lubuntu/releases/jammy/release/lubuntu-22.04.4-desktop-amd64.iso)

!!! question "为什么有这么多Ubuntu？"

    这里为什么有好几种Ubuntu，它们是什么关系？不妨查找相关资料看看是怎么回事。

### 使用WSL2搭建开发环境

应用商店即可获取，如果MS Store网络不好，也可以从微软官网获取离线安装包。

### 使用真机搭建开发环境

- 启动盘制作软件
    - [Etcher](https://etcher.balena.io/#download-etcher)
    - [Ventoy](https://www.ventoy.net/cn/download.html)
    - [软碟通](https://ultraiso.net/xiazai.html)

- [Windows镜像](https://hellowindows.cn/)（你有概率破环你的Windows！谨慎安装双系统。）

- Ubuntu2204镜像：见上方

## Linux系统的基本使用

在完成了Ubuntu的安装之后，你应该了解一些Linux的基本使用知识了；这方面的教程或者说明十分丰富。笔者自然不必赘述。

但在众多文档中，笔者尤其推荐[Linux101](https://101.ustclug.org/)，这份文档内容扎实，例子贴近实际，对使用Linux时常用到的命令与概念都有所讲解，可以使你快速上手Linux并且对它有一定的了解——而不仅仅当作一个可以装应用软件的和Windows、Android没什么两样的系统。