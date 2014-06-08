require 'formula'

class Suniq < Formula
  homepage 'https://github.com/chernjie/suniq'
  url 'https://github.com/chernjie/suniq/archive/1.0.0.tar.gz'
  sha1 '1bc7a87d895d72038b5af904d880228d925c4d73'

  def install
    system "./configure", "--disable-dependency-tracking",
                          "--prefix=#{prefix}",
                          "--mandir=#{man}"
    system "make"
    system "make install"
    bin.install_symlink "suniq" => "suniq"
  end
end
