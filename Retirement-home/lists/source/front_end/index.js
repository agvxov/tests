const profileMenuButton = document.querySelector("#user-menu-button");
const profileDropDown = document.querySelector("#profileDropDown")

const pddToggle = () => {
    profileDropDown.classList.toggle('hidden');
};

profileMenuButton.addEventListener("click", pddToggle);
window.addEventListener("click", (e) => {
    if(!profileMenuButton.contains(e.target)) {
        profileDropDown.classList.add('hidden');
    }
});

//Mobile

const mobileMenuButton = document.querySelector('#mobileMenuBtn');
const mobileMenu = document.querySelector('#mobile-menu');

const mobileNavbarToggle = () => {
    mobileMenu.classList.toggle('hidden');
    document.querySelector("#mobileMenuOpen").classList.toggle('block');
    document.querySelector("#mobileMenuOpen").classList.toggle('hidden');
    document.querySelector("#mobileMenuClose").classList.toggle('hidden');
    document.querySelector("#mobileMenuClose").classList.toggle('block');
}

mobileMenuButton.addEventListener('click', mobileNavbarToggle);