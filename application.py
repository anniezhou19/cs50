import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    records = db.execute("""SELECT symbol, SUM(shares) as total_share FROM record
    WHERE user_id=? GROUP BY symbol HAVING total_share > 0""", session["user_id"])
    holdings = []
    grand_total = 0
    for record in records:
        stock = lookup(record["symbol"])
        holdings.append({
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": record["total_share"],
            "price": usd(stock["price"]),
            "total": usd(stock["price"] * record["total_share"])
        })
        grand_total += stock["price"] * record["total_share"]
    deposit = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    cash = deposit[0]["cash"]
    grand_total += cash
    return render_template("index.html", holdings=holdings, cash=usd(cash), grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if (not request.form.get("symbol")) or (not request.form.get("shares")):
            return apology("Must provide stock symbol and number of shares", 400)
        symbol = request.form.get("symbol").upper()
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("Invalid stock symbol", 400)
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                return apology("Please provide positive integer", 400)
        except:
            return apology("Please provide positive integer", 400)
        price = stock["price"]
        rows = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        cash = rows[0]["cash"]
        total_cost = price * shares
        updated_cash = cash - total_cost
        if cash < total_cost:
            return apology("You can't afford", 400)
        else:
            db.execute("UPDATE users SET cash = ? WHERE id=?", updated_cash, session["user_id"])
            db.execute("""INSERT INTO record (user_id, symbol, name, shares, price, total) VALUES(?, ?, ?, ?, ?, ?)""",
                       session["user_id"], stock["symbol"], stock["name"], shares, price, total_cost)
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("""SELECT symbol, name, shares, price, total, time
    FROM record WHERE user_id=?""", session["user_id"])
    if not transactions:
        return apology("Sorry you have no transaction record")
    else:
        return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing stock symbol", 400)

        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("Invalid symbol", 400)
        else:
            price = usd(stock["price"])
            return render_template("quoted.html", stock=stock, price=price)
            # pass the value (stock, price) to quoted.html
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Render an apology if the user’s input is blank or the username already exists.
        if not request.form.get("username"):
            return apology("must provide username", 400)
        # Render an apology if either password input is blank or the passwords do not match.
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 400)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirmation password must be the same", 400)
        # INSERT the new user into users, storing a hash of the user’s password, not the password itself.
        # Hash the user’s password with generate_password_hash
        row = db.execute("SELECT * FROM users WHERE username=?", request.form.get("username"))
        if len(row) != 0:
            return apology("username already exists")
        user_id = db.execute("""INSERT INTO users (username, hash) VALUES (?, ?)""",
                             request.form.get("username"), generate_password_hash(request.form.get("password")))
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol is None:
            return apology("Please choose stock", 400)
        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Please provide positive integer", 400)
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid symbol", 400)
        rows = db.execute("""SELECT SUM(shares) FROM record
        WHERE user_id=? AND symbol=? GROUP BY symbol""", session["user_id"], symbol)
        own_shares = rows[0]["SUM(shares)"]
        if own_shares < shares:
            return apology("You don't have many shares of stock", 400)

        else:
            rows = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
            cash = rows[0]["cash"]
            total_sold = stock["price"] * shares
            updated_cash = cash + total_sold
            db.execute("UPDATE users SET cash=? WHERE id=?", updated_cash, session["user_id"])
            db.execute("""INSERT INTO record (user_id, symbol, name, shares, price, total) VALUES(?, ?, ?, ?, ?, ?)""",
                       session["user_id"], stock["symbol"], stock["name"], -shares, stock["price"], total_sold)
            flash("Sold!")
            return redirect("/")
    else:
        records = db.execute("""
        SELECT symbol
        FROM record
        WHERE user_id=?
        GROUP BY symbol
        HAVING SUM(shares) > 0""", session["user_id"])
        symbols = []
        for record in records:
            symbols.append(record["symbol"].upper())
        return render_template("sell.html", symbols=symbols)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":
        db.execute("""UPDATE users SET cash=cash+ :amount WHERE id = :user_id""",
                   amount=request.form.get("cash"), user_id=session["user_id"])
        flash("Added Cash!")
        return redirect("/")
    else:
        return render_template("add_cash.html")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        if not request.form.get("new_password"):
            return apology("must provide new password", 403)
        if request.form.get("new_password") != request.form.get("confirmation"):
            return apology("new_password and confirmation password must be the same")

        psw = generate_password_hash(request.form.get("new_password"))
        db.execute("UPDATE users SET hash=? WHERE id=?", psw, session["user_id"])
        return redirect("/")
    else:
        return render_template("change_password.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

