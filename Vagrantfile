# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.

Vagrant.configure(2) do |config|

  # 64 bit Ubuntu Vagrant Box, 20.04 LTS 
	# (https://app.vagrantup.com/ubuntu)
  config.vm.box = "ubuntu/focal64"

  ## Configure hostname and port forwarding
  config.vm.hostname = "cs330"
  config.ssh.forward_x11 = true
  config.vm.network "forwarded_port", guest: 8888, host: 8888
  # Assignment 6
  config.vm.network "forwarded_port", guest: 12000, host: 12000
  config.vm.network "forwarded_port", guest: 80, host: 8000


  vagrant_root = File.dirname(__FILE__)

  # Emacs settings
  config.vm.provision "file", source: "#{vagrant_root}/config_files/dot_emacs", destination: "~/.emacs"

  # Jupyter notebook settings
  config.vm.provision "file", source: "#{vagrant_root}/config_files/jupyter_notebook_config.py", destination: "~/.jupyter/jupyter_notebook_config.py"

  ## Provisioning
  config.vm.provision "shell", inline: <<-SHELL
     # Assignment 1
     sudo apt-get update
     sudo apt-get -y upgrade
     sudo apt-get install -y emacs
     sudo apt-get install -y python3-dev
     curl https://bootstrap.pypa.io/get-pip.py > get-pip.py
     sudo python3 get-pip.py
     rm -f get-pip.py
     sudo apt-get install make
     sudo apt-get install gcc
     # Install old version of tornado before installing jupyter
     #sudo pip install tornado==4.5.3
     sudo pip install tornado
     sudo pip install jupyter
     sudo apt-get install -y gccgo-go
     sudo pip install -U tzupdate
     echo "export PYTHONPATH=${PYTHONPATH}:/vagrant/course-bin" >> /home/vagrant/.profile

     # Set correct permissions for bash scripts
     find /vagrant -name "*.sh" | xargs chmod -v 744

     # If the repository was pulled from Windows, convert line breaks to Unix-style
     sudo apt-get install -y dos2unix
     printf "Using dos2unix to convert files to Unix format if necessary..."
     find /vagrant -name "*" -type f | xargs dos2unix -q

     # Previous Assignment 2 (2019 and before)
     #sudo apt-get install -y python3-tk

     # Assignment 2
     sudo pip install nbconvert
     #sudo apt-get install -y mininet
     # install mininet to work with python3
     sudo pip install mininet
     # install ryu controller
     sudo pip install ryu
     # ovs-controller is renamed to ovs-testcontroller
     sudo apt install -y openvswitch-testcontroller
     sudo ln -s /usr/bin/ovs-testcontroller /usr/bin/ovs-controller
     # also need to copy the mnexec to /usr/local/sbin
     # for whatever reason, mnexec is not built/installed

     sudo apt-get install -y python3-numpy
     sudo apt-get install -y python3-matplotlib

     # Assignment 3
     sudo apt-get install -y whois
     sudo pip install ipaddress

     # Assignment 5
     sudo apt-get install -y apache2-utils
     echo "export GOPATH=/vagrant/assignment5" >> /home/vagrant/.profile

     # Start in /vagrant instead of /home/vagrant
     if ! grep -Fxq "cd /vagrant" /home/vagrant/.bashrc
     then
      echo "cd /vagrant" >> /home/vagrant/.bashrc
     fi
  SHELL

  ## Provisioning to do on each "vagrant up"
  config.vm.provision "shell", run: "always", inline: <<-SHELL
    sudo tzupdate 2> /dev/null

    # Assignment 2
    #sudo modprobe tcp_probe port=5001 full=1
    # tcp_probe is removed from kernel.
    # https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=c3fde1bd28f7c720d7bc587e85e54706df4f8163
    # use ftrace
    sudo echo 1 > /sys/kernel/debug/tracing/events/tcp/tcp_probe/enable
  SHELL

  ## CPU & RAM
  config.vm.provider "virtualbox" do |vb|
    vb.customize ["modifyvm", :id, "--cpuexecutioncap", "100"]
    vb.memory = 2048
    vb.cpus = 1
  end

end
