# mmx-node

MMX is a blockchain written from scratch using Chia's Proof Of Space and a SHA256 VDF similar to Solana.

It's main features are as follows:
- High performance (1000 transactions per second or more)
- Variable supply (block reward scales with netspace, but also is capped by TX fees)
- Consistent block times (every 10 seconds a block is created)
- Native token support (swaps are possible with standard transactions)
- Energy saving Proof of Space (same as Chia)
- Standard ECDSA signatures for seamless integration (same as Bitcoin)

MMX is desiged to be a blockchain that can actually be used as a currency.

For example the variable supply will stabilize the price, one of the key properties of any currency.

Furthermore, thanks to an efficient implementation and the avoidance of using a virtual machine, it will provide low transaction fees even at high throughput.

Tokes can either be traditionally issued by the owner, or they can be owner-less and created by staking another token over time, in a decentralized manner governed by the blockchain.

In the future it is planned that anybody can create their own token on MMX using a simple web interface.

In addition the first application for MMX will be a decentralized exchange where users can trade MMX and tokens.

The variable reward function is as follows: \
`reward = max(max(difficulty * const_factor, min_reward), TX fees)`. \
Where `min_reward` and `const_factor` are fixed at launch.

A mainnet launch is planned in ~6 months or so.
Currently we are running the _first testnet_, so the coins farmed right now are _not worth anything_.

## CLI

To use the CLI:
```
cd mmx-node
source ./activate.sh
```

The node needs to be running, see below how to start it.

To check your balance: `mmx wallet show`

To show wallet activity: `mmx wallet log`

To show the first 10 addresses: `mmx wallet show 10`

To get a specific receiving address: `mmx wallet get address [index]`

To send coins: `mmx wallet send -a <amount> -t <address>`

To get the seed value from a wallet: `mmx wallet get seed`

To use a non-default wallet specify `-j <index>` with above commands (at the end).

To check on the node: `mmx node info`

To check on the peers: `mmx node peers`

To check on a transaction: `mmx node tx <txid>`

To check the balance of any address: `mmx node balance <address>`

To dump a transaction: `mmx node get tx <txid>`

To dump a block: `mmx node get block <height>`

To dump a block header: `mmx node get header <height>`

To force a re-sync: `mmx node sync`

To get connected peers: `mmx node get peers`

To check on the farm: `mmx farm info`

To get total space in bytes: `mmx farm get space`

To show plot directories: `mmx farm get dirs`

To reload plots: `mmx farm reload`

## Setup

First finish the installtion step below.

To continue enter the CLI environment:
```
cd mmx-node
source ./activate.sh
```

### Creating a Wallet

```
mmx wallet create [-f filename]
```

The file name argument is optional, by default it is `wallet.dat`, which is already included in the default configuration.

To use more wallets add the paths to `key_files+` array in `config/local/Wallet.json`.

To create a wallet with a known seed value:
```
mmx wallet create <seed> [-f filename]
```

To get the seed value from a wallet:
```
mmx wallet get seed [-j index]
```

## Running a Node

First perform the installation and setup steps.

To run a node for current `testnet1`
```
./run_node.sh
```

You can enable port forwaring on TCP port 12331 if you want to help out the network and accept incoming connections.

To run a node in the background you can enter a `screen` session:
```
screen -S node
(start node as above)
<Ctrl+A> + D (to detach)
screen -r node (to attach again)
```

To disable the `TimeLord` specify `--timelord 0` on the command line.
Alternatively, you can also disable it by default: `echo false > config/local/timelord`.
If you have a slow CPU this is recommended and maybe even needed to stay in sync.

To re-sync starting from a specific height: `--Node.replay_height <height>`.
This is needed if for some reason you forked from the network.
To re-sync from scratch delete `block_chain.dat`.

## Plotting

To get the farmer and pool keys for plotting:
```
mmx wallet keys [-j index]
```

The node needs to be running for this command to work. (`-j` to specify the index of a non-default wallet)

Then use my plotter with `-x 11337` argument: https://github.com/madMAx43v3r/chia-plotter

The minimum K size for mainnet will probably be k30, for testnets it is k26. The plots from testnets can be reused for mainnet later.
It's possible there will be a time limit for k30 and k31 though, something like 3 years for k30 and 6 years for k31, to prevent grinding attacks in the future.

To add a plot directory add the path to `plot_dirs` array in `config/local/Harvester.json`, for example:
```
{
	"plot_dirs": ["/mnt/drive1/plots/", "/mnt/drive2/plots/"]
}
```

## Installation

Ubuntu Linux:
```
sudo apt update
sudo apt install git cmake build-essential libsecp256k1-dev libsodium-dev zlib1g-dev ocl-icd-opencl-dev clinfo screen
```

Arch Linux:
```
sudo pacman -Syu
sudo pacman -S base-devel git cmake zlib libsecp256k1 libsodium ocl-icd clinfo screen
```

OpenCL provides faster and more effient VDF verification using an integrated or dedicated GPU.
A standard iGPU found in Intel CPUs with 192 shader cores is plenty fast enough.
If you dont have a fast quad core CPU (>3 GHz) or higher core count CPU, it is required to have a GPU with OpenCL support.

Make sure to be in the `video` and or `render` group (depends on distribution) to be able to access a GPU:
```
sudo adduser $USER video
sudo adduser $USER render
```

### Building

```
git clone https://github.com/madMAx43v3r/mmx-node.git
cd mmx-node
git submodule update --init --recursive
./make_devel.sh
```

To update to latest version:
```
./update.sh
```

### Windows via WSL

To setup Ubuntu 20.04 in WSL on Windows you can follow the tutorial over here: \
https://docs.microsoft.com/en-us/learn/modules/get-started-with-windows-subsystem-for-linux/

Make sure to install Ubuntu in step 2: https://www.microsoft.com/store/p/ubuntu/9nblggh4msv6

Then type "Ubuntu" in the start menu and start it, you will be asked to setup a user and password.
After that you can follow the normal instructions for Ubuntu 20.04.

To get OpenCL working in WSL:
https://devblogs.microsoft.com/commandline/oneapi-l0-openvino-and-opencl-coming-to-the-windows-subsystem-for-linux-for-intel-gpus/

### Using packaged secp256k1

If you don't have a system package for `libsecp256k1`:
```
cd mmx-node/secp256k1
./autogen.sh
./configure
make -j8
cd ..
./make_devel.sh -DWITH_SECP256K1=1
```

### OpenCL for Intel iGPUs

Ubuntu 20.04, 21.04
```
sudo apt install intel-opencl-icd
```

Ubuntu ppa for 18.04, 20.04, 21.04
```
sudo add-apt-repository ppa:intel-opencl/intel-opencl
sudo apt update
sudo apt install intel-opencl-icd
```

For older Intel CPUs like `Ivy Bridge` or `Bay Trail` you need this package:
```
sudo apt install beignet-opencl-icd
```

Make sure your iGPU is not somehow disabled, like here for example: https://community.hetzner.com/tutorials/howto-enable-igpu

### OpenCL for AMD GPUs

Linux: \
https://www.amd.com/en/support/kb/release-notes/rn-amdgpu-unified-linux-21-20 \
https://www.amd.com/en/support/kb/release-notes/rn-amdgpu-unified-linux-21-30

```
./amdgpu-pro-install -y --opencl=pal,legacy
```

Windows: https://google.com/search?q=amd+graphics+driver+download

### OpenCL for Nvidia GPUs

Install CUDA, may the force be with you: \
https://www.google.com/search?q=nvidia+cuda+download

Arch Linux:
```
sudo pacman -S nvidia nvidia-utils opencl-nvidia
```
