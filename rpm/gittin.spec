
Summary: A library to hangle Git repositories
Name: gittin
Version: 0.1.3
Release: 2
License: LGPLv2.1
Group: Development/Libraries
URL: https://git.jollamobile.com/vault/gittin
Source0: %{name}-%{version}.tar.bz2
BuildRequires: cmake >= 2.8.9
BuildRequires: pkgconfig(Qt5Core)
Requires: git-minimal >= 1.7
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
A library to hangle Git repositories

%package devel
Summary: gittin headers etc.
Requires: %{name} = %{version}-%{release}
%description devel
gittin library header files etc.

%prep
%setup -q

%build
%cmake -DVERSION=%{version} %{?_with_multiarch:-DENABLE_MULTIARCH=ON}
make %{?jobs:-j%jobs}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=%{buildroot}

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_libdir}/libgittin.so

%files devel
%defattr(-,root,root,-)
%{_libdir}/pkgconfig/*.pc
%dir %{_includedir}/gittin
%{_includedir}/gittin/*.hpp


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig
