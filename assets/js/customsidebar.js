class CustomSideBar extends HTMLElement{
    connectedCallback() {
        this.innerHTML = `
        <!-- Header -->
        <header id="header">
            <div class="inner">
                <a href="#" class="image avatar"><img src="images/profile.JPG" alt="" /></a>
                <h1>
                    <strong>Denis Mayr Lima Martins</strong>, 
                    <br />
                    <strong><a href="http://erc.is/p/martins" target="_blank">PostDoc</a> researcher at the <a href="https://www.wi.uni-muenster.de/department/dasc" target="_blank">MLDE  group</a>, 
                    <br />
                    Univeristy of Münster, Germany.</strong>
                </h1>
                <nav id="nav">
                    <ul>
                        <li><a href="index.html">Home</a></li>
                        <li><a href="publications.html">Publications</a></li>
                        <li><a href="teaching.html">Teaching</a></li>
                    </ul>
                </nav>
            </div>
        </header>
        <!-- Footer -->
        <footer id="footer">
            <div class="inner">
                <ul class="icons">
                    <li><a href="http://www.researchgate.net/profile/Denis_Martins" class="icon brands fa-researchgate"><span class="label">Research Gate</span></a></li>
                    <li><a href="https://github.com/denmartins" class="icon brands fa-github"><span class="label">Github</span></a></li>
                    <li><a href="http://twitter.com/denmartins" class="icon brands fa-twitter"><span class="label">Twitter</span></a></li>
                </ul>
                <ul class="copyright">
                    <li>&copy; Denis Martins</li><li>Design: <a href="http://html5up.net">HTML5 UP</a></li>
                </ul>
            </div>
        </footer>
        `
    }
}

customElements.define('side-bar', CustomSideBar)